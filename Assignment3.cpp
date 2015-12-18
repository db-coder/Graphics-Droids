/*
  CSX75 Tutorial 3

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Modified from An Introduction to OpenGL Programming, 
  Ed Angel and Dave Shreiner, SIGGRAPH 2013

  Written by - 
               Harshavardhan Kode
  Further modified by: Dibyendu Mondal and Anand Bhoraskar
*/


#include "Assignment3.hpp"
#include "models.cpp"
#include "texture.cpp"


GLuint shaderProgram;
GLuint tex;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;


glm::mat4 modelview_matrix;
glm::mat3 normal_matrix;

GLuint uModelViewMatrix;
GLuint viewMatrix;
GLuint normalMatrix;
GLuint Light;
GLuint spot;

//-----------------------------------------------------------------

vector<glm::vec4> v_positions;
vector<glm::vec4> v_colors;
vector<glm::vec4> v_normals;
vector<glm::vec2> tex_coords;
vector<glm::vec2> v_textures;

vector<glm::vec4> v_positions1[3];
vector<glm::vec4> v_colors1[3];
vector<glm::vec4> v_normals1[3];
vector<glm::vec2> v_textures1[3];

//-----------------------------------------------------------------

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("vshader.glsl");
  std::string fragment_shader_file("fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  vNormal = glGetAttribLocation( shaderProgram, "vNormal" ); 
  texCoord = glGetAttribLocation( shaderProgram, "texCoord" );
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");
  normalMatrix =  glGetUniformLocation( shaderProgram, "normalMatrix");
  viewMatrix = glGetUniformLocation( shaderProgram, "viewMatrix");
  Light = glGetUniformLocation( shaderProgram, "Light");
  spot = glGetUniformLocation( shaderProgram, "spot");

  // Load Textures 
  GLuint tex=LoadTexture("images/lava.bmp",205,205);
  GLuint tex1=LoadTexture("images/texture1.bmp",256,256);
  GLuint tex2=LoadTexture("images/all1.bmp",256,256);
  GLuint tex3=LoadTexture("images/steelDark.bmp",432,324);
  GLuint tex4=LoadTexture("images/blue.bmp",251,201);
  GLuint tex5=LoadTexture("images/ground1.bmp",512,512);
  GLuint tex6=LoadTexture("images/night.bmp",1024,768);
  //note that the buffers are initialized in the respective constructors

  //Ground
  cuboid(v_positions, v_colors, v_normals, tex_coords, -40.0, 40.0, 5.0, 20.0, 2);
  node00 = new csX75::HNode(NULL,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex5);
  node00->change_parameters(0.0,-6.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  tex_coords.clear();

  int Lat = tesselation;
  int Long = tesselation;
  //Sky
  // cuboid(v_positions, v_colors, v_normals, tex_coords, -50.0, 50.0, 50.0, 50.0, 2);
  sphere(50.0, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  node01 = new csX75::HNode(NULL,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex6);
  node01->change_parameters(0.0,3.0,-20.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  v_textures.clear();
  tex_coords.clear();

 // Call the sphere function
  sphere(0.1, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  sphere(1.0, Lat, Long, v_positions1[0], v_colors1[0], v_normals1[0], v_textures1[0]);
  head(0.5,  Lat, Long,1.2, v_positions1[1], v_colors1[1], v_normals1[1], v_textures1[1]);
  goggles(0.5,  0.25,0, v_positions1[2], v_colors1[2], v_normals1[2], v_textures1[2]);

  node0 = new csX75::HNode(NULL,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex1);
  node0->change_parameters(-4.0,0.0,0.0,0.0,0.0,0.0);
  node1 = new csX75::HNode(node0,v_positions1[0].size(),&(v_positions1[0][0]),&(v_colors1[0][0]),&(v_normals1[0][0]),&(v_textures1[0][0]),sizeof(glm::vec4)*(v_positions1[0].size()),sizeof(glm::vec4)*(v_colors1[0].size()),sizeof(glm::vec4)*(v_normals1[0].size()),sizeof(glm::vec2)*(v_textures1[0].size()),tex1);
  node2 = new csX75::HNode(node0,v_positions1[1].size(),&(v_positions1[1][0]),&(v_colors1[1][0]),&(v_normals1[1][0]),&(v_textures1[1][0]),sizeof(glm::vec4)*(v_positions1[1].size()),sizeof(glm::vec4)*(v_colors1[1].size()),sizeof(glm::vec4)*(v_normals1[1].size()),sizeof(glm::vec2)*(v_textures1[1].size()),tex2);
  node2->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  node3 = new csX75::HNode(node2,v_positions1[2].size(),&(v_positions1[2][0]),&(v_colors1[2][0]),&(v_normals1[2][0]),&(v_textures1[2][0]),sizeof(glm::vec4)*(v_positions1[2].size()),sizeof(glm::vec4)*(v_colors1[2].size()),sizeof(glm::vec4)*(v_normals1[2].size()),sizeof(glm::vec2)*(v_textures1[2].size()),tex1);
  node3->change_parameters(0.0,1.2,0.0,0.0,0.0,0.0);
  root_node = node0;
  v_positions.clear();
  v_colors.clear();
  tex_coords.clear();
  v_normals.clear();
  v_textures.clear();

  // cuboid(v_positions, v_colors, v_normals, tex_coords, 1.0, -1.0, 1.0, 0.5, 4);    //body
  torso(v_positions, v_colors, v_normals, tex_coords,0.5,1,0.25,1.6,0.8,2);    //body
  node20 = new csX75::HNode(NULL,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex);
  node20->change_parameters(1.0,-0.2,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  // cuboid(v_positions, v_colors, v_normals, tex_coords, 0.5, -0.5, 0.5, 0.25, 2);    //head
  head(0.6, Lat, Long, 0, v_positions, v_colors, v_normals, tex_coords);    //head
  node10 = new csX75::HNode(node20,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex4);
  node10->change_parameters(0.0,2.2,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);             //right arm
  int num_vertices=v_positions.size();
  node21 = new csX75::HNode(node20,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node21->change_parameters(0.9,1.5,0.0,0.0,0.0,45.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  sphere(0.15, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  node22 = new csX75::HNode(node21,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex);
  node22->change_parameters(0.0,-0.4,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  v_textures.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);
  node23 = new csX75::HNode(node22,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node23->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  //left arm
  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);
  node31 = new csX75::HNode(node20,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node31->change_parameters(-0.9,1.5,0.0,0.0,0.0,-45);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  sphere(0.15, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  node32 = new csX75::HNode(node31,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex);
  node32->change_parameters(0.0,-0.4,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  v_textures.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);
  node33 = new csX75::HNode(node32,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node33->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);             //right leg
  num_vertices=v_positions.size();
  node41 = new csX75::HNode(node20,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node41->change_parameters(0.5,0.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  sphere(0.15, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  node42 = new csX75::HNode(node41,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex);
  node42->change_parameters(0.0,-0.4,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  v_textures.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);
  node43 = new csX75::HNode(node42,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node43->change_parameters(0.0,0,0.0,0.0,0.0,0.0);

  //left leg
  node51 = new csX75::HNode(node20,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node51->change_parameters(-0.5,0.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  sphere(0.15, Lat, Long, v_positions, v_colors, v_normals, v_textures);
  node52 = new csX75::HNode(node51,v_positions.size(),&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(v_textures[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(v_textures.size()),tex);
  node52->change_parameters(0.0,-0.4,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  v_textures.clear();

  cylinder(v_positions, v_colors, v_normals, tex_coords, 0.1, 0.4, 3);
  node53 = new csX75::HNode(node52,num_vertices,&(v_positions[0]),&(v_colors[0]),&(v_normals[0]),&(tex_coords[0]),sizeof(glm::vec4)*(v_positions.size()),sizeof(glm::vec4)*(v_colors.size()),sizeof(glm::vec4)*(v_normals.size()),sizeof(glm::vec2)*(tex_coords.size()),tex3);
  node53->change_parameters(0.0,0.0,0.0,0.0,0.0,0.0);
  v_positions.clear();
  v_colors.clear();
  v_normals.clear();
  tex_coords.clear();

  root_node = curr_node = node20;
}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // //ground
  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,150.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 150.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  node00->render_tree();

  //robot
  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,150.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 150.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  node20->render_tree();

  //sphere
  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,150.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 150.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  node0->render_tree();

  //sky
  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    // projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,150.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -10.0, 150.0);

  view_matrix = projection_matrix*lookat_matrix;

  matrixStack.push_back(view_matrix);

  node01->render_tree();

}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(1024, 1024, "CS475/CS675 Assignment 3: Modelling and Rendering", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

