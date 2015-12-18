#version 330

in vec2 tex;
in vec3 normal;
in vec4 eye;
in vec4 COLOR;
in vec4 Act_Position;
out vec4 frag_color;

uniform int Light;
uniform int spot;
uniform mat4 viewMatrix;
uniform sampler2D texture;

void main () 
{
	vec4 texture1 = texture2D(texture, tex);
  // Defining Materials
  vec4 diffuse = vec4(0.5, 0.5, 0.5, 1.0); 
  vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
  vec4 specular = vec4(0.5, 0.5, 0.5, 1.0);
  float shininess = 1.0;
  vec4 spec = vec4(0.0), spec1 = vec4(0.0); 

  // Defining Light 
  vec4 lightPos = vec4(1.0, 5.0, -10.0, 1.0);
  vec3 lightDir = vec3(viewMatrix * lightPos);  // Transforms with camera
  lightDir = normalize( vec3(lightDir));  

  //Diffuse
  vec3 n = normalize(vec3(normal));	     
  float dotProduct = dot(n, lightDir);
  float intensity =  max( dotProduct, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity > 0.0)
  {
	vec3 e = normalize(vec3(eye));
	vec3 h = normalize(lightDir + e );
  float intSpec = max(dot(h,n), 0.0);	
  spec = specular * pow(intSpec, shininess);
  }  

  // Defining Light 
  vec4 lightPos1 = vec4(-10.0, 20.0, 10.0, 1.0);
  vec3 lightDir1 = vec3(viewMatrix * lightPos1);  // Transforms with camera
  lightDir1 = normalize( vec3(lightDir1));  

  //Diffuse     
  float dotProduct1 = dot(n, lightDir1);
  float intensity1 =  max( dotProduct1, 0.0);

  // Compute specular component only if light falls on vertex
  if(intensity1 > 0.0)
  {
	vec3 e1 = normalize(vec3(eye));
	vec3 h1 = normalize(lightDir1 + e1 );
  float intSpec1 = max(dot(h1,n), 0.0);	
  spec1 = specular * pow(intSpec1, shininess);
  }  

  // Defining SpotLight 
  vec4 spotlightPos = vec4(0.2, 10.0, 0.5, 1.0);
  vec4 spotlightPos1 = vec4(0.0, 8.0, 0.0, 1.0);
  vec3 lightDir2 = vec3(viewMatrix*spotlightPos - Act_Position);
  lightDir2 = normalize( vec3(lightDir2));


  vec3 n_spot = normalize(vec3(normal));
  //Diffuse     
  float dotProduct2 = dot(n_spot, lightDir2);
  float intensity2 =  max( dotProduct2, 0.0);

  vec4 spec2 = vec4(0.0);
	if(intensity2 > 0.0)
  {
	vec3 e3 = normalize(vec3(eye));
	vec3 h3 = normalize(lightDir2 + e3 );
  float intSpec3 = max(dot(h3,n_spot), 0.0);	
  spec2 = specular * pow(intSpec3, shininess);
  }

  float dotProduct3 = dot(normalize(vec3(viewMatrix*(spotlightPos - spotlightPos1))),lightDir2);
  float intensity3 = max(dotProduct3,0.0);

  vec4 color = vec4(0.0);
  if(Light==0)
  {	
  	color = ambient*texture1; // All
  }
  else if(Light==1)
  {	
  	color = (intensity * diffuse  + spec)*texture1+ ambient*texture1; // All
  }
  else
  {	
  	color = (intensity * diffuse  + spec)*texture1 + (intensity1 * diffuse  + spec1)*texture1 + ambient*texture1; // All
  }
  if (spot==1)
  {
  	if (intensity3 > 0.9)
  	{
  		color += (intensity2*diffuse + spec2)*texture1;
  	}
  }
  //vec4 color = max(intensity * diffuse * texture1, ambient); // Only Diffuse  
  frag_color = color;
}
