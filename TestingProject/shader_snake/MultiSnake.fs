#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect SourceImage;		// Source picture to be processed
uniform sampler2DRect MatrixH;
uniform sampler2DRect MatrixV;

uniform int   iWidth; 
uniform int   iHeight;

void main()
{
	int i, j;			// Filter iterators
	int y, x;			// Image iterators
	vec3 img, filter_h, filter_v;
	vec3 res_h = vec3(0.0);
	vec3 res_v = vec3(0.0);
	for (i = 0, y = int(gl_TexCoord[0].y - 1); i < 3; i++, y++)
	{
		for (j = 0, x = int(gl_TexCoord[0].x - 1); j < 3; j++, x++)
		{
			if ((x >= 0) && (x < iWidth) && (y >= 0) && (y < iHeight))
			{
				img = texture2DRect(SourceImage, vec2(x, y)).xyz;
				filter_h = texture2DRect(MatrixH, vec2(j, i)).xyz;
				filter_v = texture2DRect(MatrixV, vec2(j, i)).xyz;
							
				res_h = res_h + img * filter_h;
				res_v = res_v + img * filter_v;
			}
		}
	}
	
	gl_FragData[0] = vec4(res_h, 0.0F);
	gl_FragData[1] = vec4(res_v, 0.0F);
}