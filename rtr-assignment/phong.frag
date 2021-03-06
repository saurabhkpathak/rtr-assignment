varying vec3 N;
varying vec3 v;
void main (void)
{
vec3 L = normalize(gl_LightSource[0].position.xyz - v);
// we are in Eye Coordinates, so EyePos is (0,0,0)
vec3 E = normalize(-v);
vec3 R = normalize(-reflect(L,N));
//calculate Ambient Term:
vec4 Iamb = gl_FrontLightProduct[0].ambient * gl_FrontMaterial.ambient;
//calculate Diffuse Term:
vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0) * gl_FrontMaterial.diffuse;
Idiff = clamp(Idiff, 0.0, 1.0);
// calculate Specular Term:
vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0), gl_FrontMaterial.shininess);
Ispec = clamp(Ispec, 0.0, 1.0);
// write Total Color:
gl_FragColor = Iamb + Idiff + Ispec;
}