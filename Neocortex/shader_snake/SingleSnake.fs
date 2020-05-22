#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect Image;
uniform sampler2DRect Points;

uniform int   iSize; 
uniform int   iWindow;
uniform int   iWidth;
uniform int   iHeight;
uniform float fGamma;
uniform float fAvgDist;
uniform vec3  vParam;

void main()
{
	int i = int(gl_TexCoord[0].x);

	vec3 p_left;
	vec3 p_center = texture2DRect(Points, vec2(i, 0)).xyz;
	vec3 p_right;
	if (i == 0)
	{
		p_left = texture2DRect(Points, vec2(iSize, 0)).xyz;
	}
	else
	{
		p_left = texture2DRect(Points, vec2(i - 1, 0)).xyz;

	}
	if (i == iSize - 1)
	{
		p_right = texture2DRect(Points, vec2(0, 0)).xyz;
	}
	else
	{
		p_right = texture2DRect(Points, vec2(i + 1, 0)).xyz;

	}
		
	// Window region
	float fWindow = float(iWindow);
	int x_s = int(max(p_center.x - fWindow, 0.0));
	int y_s = int(max(p_center.y - fWindow, 0.0));
	int x_e = int(min(p_center.x + fWindow, float(iWidth - iWindow - 1)));
	int y_e = int(min(p_center.y + fWindow, float(iHeight - iWindow - 1)));
	
	// Point normal
	vec3 nrm_1 = normalize(vec3(p_center.y - p_left.y, p_left.x - p_center.x, 0.0));
	vec3 nrm_2 = normalize(vec3(p_right.y - p_center.y, p_center.x - p_right.x, 0.0));
	vec3 nrm = p_center + fWindow * normalize(nrm_1 + nrm_2);

	vec3 max_e = vec3(0.0);
	vec3 min_e = vec3(1e38);
	int x, y, m;
	vec3 e_map[50];
	
	// Build energy map
	m = 0;
	for (y = y_s; y <= y_e; y++)
	{
		for (x = x_s; x <= x_e; x++)
		{
			vec3 p = vec3(x, y, 0.0);

			e_map[m].x = abs(fAvgDist - distance(p_left, p) - distance(p_right, p));
			e_map[m].y = pow(length(2 * p - p_left - p_right), 2.0);
			e_map[m].z = distance(p, nrm);
		
			max_e = max(e_map[m], max_e);
			min_e = min(e_map[m], min_e);
			
			m++;
		}
	}
	int area = m;
	
	// Normalize the energies
	vec3 delta_e = max_e - min_e;
	delta_e.x = ((delta_e.x == 0.0) ? 0.0 : 1.0 / delta_e.x);
	delta_e.y = ((delta_e.y == 0.0) ? 0.0 : 1.0 / delta_e.y);
	delta_e.z = ((delta_e.x == 0.0) ? 0.0 : 1.0 / delta_e.z);

	for(m = 0; m < area; m++)
	{
		e_map[m] = (e_map[m] - min_e) * delta_e;
	}
	
	// Apply parameters and find the least energy point
	float min_rslt = 1e38;
	float rslt;
	vec3 out_point=vec3(0.0,0.0,0.0);
	
	m = 0;
	for (y = y_s; y <= y_e; y++)
	{
		for (x = x_s; x <= x_e; x++)
		{
			rslt = dot(vParam, e_map[m]) + fGamma * texture2DRect(Image, vec2(x, y)).x ;
			if (rslt < min_rslt)
			{
				min_rslt = rslt;
				out_point = vec3(x, y, 0.0);
			}
			
			m++;
		}
	}
	
	gl_FragData[0] = vec4(out_point, 0.0F);
}