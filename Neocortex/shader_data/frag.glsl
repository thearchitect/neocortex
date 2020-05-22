uniform sampler3D myTexture;

uniform int startLayer, endLayer;
uniform float pCoordPerLayer;
uniform float layerDistance;

uniform float multCoeff;

uniform float distance;
uniform float rotPhi, rotTheta;

uniform float alphaTestValue;

vec3 bmin;
vec3 bmax;

struct Ray {
    vec3 origin;
    vec3 direction;
};

struct Camera {
    vec3 position;
    vec3 up;
    vec3 side;
    vec3 view;
};

bool IntersectBox ( in Ray ray, in vec3 minimum, in vec3 maximum, out float start, out float final) {
    vec3 OMIN = (minimum - ray.origin) / ray.direction;
    vec3 OMAX = (maximum - ray.origin) / ray.direction;

    vec3 MAX = max(OMAX, OMIN);
    vec3 MIN = min(OMAX, OMIN);

    final = min(MAX.x, min(MAX.y, MAX.z));
    start = max(max(MIN.x, 0.0), max(MIN.y, MIN.z));

    return final > start;
}

float GetClosest(float pCoord, out int curLayer) {
    float res;
    if (abs(pCoordPerLayer * float(curLayer) - pCoord) <
        abs(pCoordPerLayer * float(curLayer + 1) - pCoord)) {
        res = pCoordPerLayer * float(curLayer);
    } else {
        res = pCoordPerLayer * float(curLayer + 1);
    }
    return res;
}

vec3 Raytrace(in Ray ray) {
    float start, final, time;

    //float finalZ = (endLayer - startLayer) * layerDistance;
    float step = (final - start) / 2.0;
    step = layerDistance;

    vec3 res = vec3(gl_TexCoord[0].st, 0);

    bmin = vec3(-1.0, -1.0, -float(endLayer - startLayer) * layerDistance * 0.5 - 0.0001);
    bmax = vec3(+1.0, +1.0, +float(endLayer - startLayer) * layerDistance * 0.5 + 0.0001);
    if (IntersectBox(ray, bmin, bmax, start, final)) {
        res = vec3(0.0);
        vec3 point = ray.origin + ray.direction * final;
        int curLayer = 0;

        while (point.z >= bmin.z - 0.0001 && point.z <= bmax.z + 0.0001 &&
               point.x >= bmin.x && point.x <= bmax.x &&
               point.y >= bmin.y && point.y <= bmax.y ) {

            float pCoord = 1.0 - (point.z - bmin.z) / (bmax.z - bmin.z);
                                                                                
            pCoord = pCoord * pCoordPerLayer * float(endLayer - startLayer) + float(startLayer + 1)* pCoordPerLayer;
            /*
            float closerPCoord = GetClosest(pCoord, curLayer);
            if (closerPCoord >= pCoord) {
                curLayer++;
            }
            //*/
                   
            vec3 texCoord = vec3((point.x - bmin.x) / (bmax.x - bmin.x),
                                 (point.y - bmin.y) / (bmax.y - bmin.y),
                                 pCoord);
            //res += vec3(texture3D(myTexture, texCoord).a) * 1.0;
            float cur = texture3D(myTexture, texCoord).a;
            if (cur >= alphaTestValue) {
                res = mix(res, cur * multCoeff, cur * 1.1);
            }

            point -= step * ray.direction;
        }
        //res = vec3(texture3D(myTexture, vec3(gl_TexCoord[0].ts, 0)).a);
    }

    return res;
}

void main(void) {
    //gl_FragColor = vec4 ( gl_TexCoord[0].st, 0, 1 );

    layerDistance /= 70000.0;

    Camera camera;

    //camera.position = vec3(0, 0, -4.5);
    //distance = 3.5;
    float anglePhi = 3.14159 / 180.0 * rotPhi;
    float angleTheta = 3.14159 / 180.0 * (rotTheta + 90.0);

    //angleTheta = 3.1459 / 2.0;
    //anglePhi = 0;

    camera.position = vec3(distance * sin(angleTheta) * sin(anglePhi),
                           distance * cos(angleTheta),
                          -distance * sin(angleTheta) * cos(anglePhi));
                          //-3.5);
    camera.view = -normalize(camera.position);
    camera.up = normalize(vec3(camera.position.x, camera.position.z, -camera.position.y));
    //camera.up = normalize(vec3(0,sin(angleTheta),cos(angleTheta)));
    //camera.up = vec3(0, 1, 0);
    //camera.up = normalize(vec3(camera.view.x,
    //                         -(camera.view.z*camera.view.z + camera.view.x*camera.view.x) / camera.view.y,
    //                           camera.view.z));
    //camera.up = -normalize((-cos(anglePhi)*camera.up + sin(anglePhi) * cross(vec3(0, 1, 0), -camera.up))); 
    camera.side = normalize(cross(camera.view, camera.up));

    vec3 direction = camera.view - camera.side * (0.5 - gl_TexCoord[0].t) - camera.up * (0.5 - gl_TexCoord[0].s);
    
    Ray ray = Ray(camera.position, normalize(direction));

    gl_FragColor = vec4(Raytrace(ray) * multCoeff, 1.0);

    //gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, pCoord, 0.0)).a) * multCoeff;
    //gl_FragColor = vec4(texture3D(myTexture, vec3(1.0 - gl_TexCoord[0].t, 1.0 - gl_TexCoord[0].s, 0)).a) * multCoeff;
}