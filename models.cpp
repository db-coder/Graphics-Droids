#include <vector>
using namespace std;
int tesselation=50; 
double PI=3.14159265;

const int num_vertices = 100000;

glm::vec4 white(1.0, 1.0, 1.0, 1.0);

glm::vec2 t_coords[4] = {
  glm::vec2( 0.0, 0.0),
  glm::vec2( 0.0, 1.0),
  glm::vec2( 1.0, 0.0),
  glm::vec2( 1.0, 1.0)
};

void sphere(double radius, int Lats, int Longs, vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& v_textures)
{

  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  glm::vec4 prev_point1,prev_point2;
  glm::vec2 prev_point1Tex,prev_point2Tex;

  for (lats = 0.0; lats <= PI; lats+=sectors)  
  {
    for(longs = 0.0; longs <= 2*PI; longs+=slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(longs);
      float y = radius * cos(lats);
      glm::vec4 pt1(x, y, z, 1.0);
      glm::vec2 pt1Tex(lats/PI,longs/(2*PI));

      
      if(lats+sectors>PI)
        l=PI;
      else
        l=lats+sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(longs);
      y = radius * cos(l);
      glm::vec4 pt2(x, y, z, 1.0);
      glm::vec2 pt2Tex(l/PI,longs/(2*PI));

      if (!(lats==0.0 && longs==0.0))
      {
        v_colors.push_back(white);
        v_positions.push_back(pt1); 
        v_normals.push_back(pt1);
        v_textures.push_back(pt1Tex);

        v_colors.push_back(white);
        v_positions.push_back(pt2); 
        v_normals.push_back(pt2);
        v_textures.push_back(pt2Tex);
        
        v_colors.push_back(white);
        v_positions.push_back(prev_point1); 
        v_normals.push_back(prev_point1);
        v_textures.push_back(prev_point1Tex); 


        v_colors.push_back(white);
        v_positions.push_back(pt2); 
        v_normals.push_back(pt2);
        v_textures.push_back(pt2Tex);
        
        v_colors.push_back(white);
        v_positions.push_back(prev_point1); 
        v_normals.push_back(prev_point1); 
        v_textures.push_back(prev_point1Tex);

        v_colors.push_back(white);
        v_positions.push_back(prev_point2); 
        v_normals.push_back(prev_point2); 
        v_textures.push_back(prev_point2Tex);
      }

      prev_point1=pt1;
      prev_point2=pt2;

      prev_point1Tex=pt1Tex;
      prev_point2Tex=pt2Tex;
    }
  }
}


void head(double radius, int Lats, int Longs, float height , vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& v_textures)
{

  float lats,longs;

  float slices=(180/(float(Lats)*10))/2;
  float sectors=(180/(float(Longs)*10))/2;

  float l;
  glm::vec4 prev_point1,prev_point2;
  glm::vec4 prev_normal1,prev_normal2;
  glm::vec2 prev_point1Tex,prev_point2Tex;

  for (lats = 0.0; lats <= 5*PI/8; lats+=sectors)  
  {
    for(longs = 0.0; longs <= 2.0*PI; longs+=slices)
    {
      float x = radius * sin(lats) * cos(longs);
      float z = radius * sin(lats) * sin(longs);
      float y = radius * cos(lats);
      glm::vec4 pt1(x, y + height, z, 1.0);
      glm::vec4 normal1(x, y, z, 1.0);
      glm::vec2 pt1Tex(lats/PI,longs/(2*PI));
      
      if(lats+sectors>PI)
        l=PI;
      else
        l=lats+sectors;
      x = radius * sin(l) * cos(longs);
      z = radius * sin(l) * sin(longs);
      y = radius * cos(l);
      glm::vec4 pt2(x, y + height, z, 1.0);
      glm::vec4 normal2(x, y , z, 1.0);
      glm::vec2 pt2Tex(l/PI,longs/(2*PI));

      if (!(lats==0.0 && longs==0.0))
      {   
        v_colors.push_back(white);
        v_positions.push_back(pt1); 
        v_normals.push_back(normal1);
        v_textures.push_back(pt1Tex);

        v_colors.push_back(white);
        v_positions.push_back(pt2); 
        v_normals.push_back(normal2);
        v_textures.push_back(pt2Tex);
        
        v_colors.push_back(white);
        v_positions.push_back(prev_point1); 
        v_normals.push_back(prev_normal1); 
        v_textures.push_back(prev_point1Tex); 


        v_colors.push_back(white);
        v_positions.push_back(pt2); 
        v_normals.push_back(normal2);
        v_textures.push_back(pt2Tex);
        
        v_colors.push_back(white);
        v_positions.push_back(prev_point1); 
        v_normals.push_back(prev_normal1);
        v_textures.push_back(prev_point1Tex);

        v_colors.push_back(white);
        v_positions.push_back(prev_point2); 
        v_normals.push_back(prev_normal2);
        v_textures.push_back(prev_point2Tex);
      }
      prev_point1=pt1;
      prev_point2=pt2;

      prev_point1Tex=pt1Tex;
      prev_point2Tex=pt2Tex;

      prev_normal1=normal1;
      prev_normal2=normal2;
    }
  }
}

void goggles(double headRadius, double goggleRadius, float height, vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& v_textures)
{
  float z = headRadius;

  float centreX = -goggleRadius,centreY = headRadius/2;

  float k = 12;

  for(;centreX<=2*goggleRadius;centreX+=2*goggleRadius)
    for (float theta = 0; theta + PI/k < PI; theta=theta + (PI/k) )
    {
      glm::vec4 pt1(centreX + goggleRadius*cos(theta),centreY - goggleRadius*sin(theta) ,z,1.0),
                pt2(centreX + goggleRadius*cos(theta+PI/k),centreY - goggleRadius*sin(theta+PI/k) ,z,1.0),
                pt3(centreX,centreY ,z,1.0),
                nrm(0,0,z,1);
      v_positions.push_back(pt1);
      v_positions.push_back(pt2);
      v_positions.push_back(pt3);
      v_colors.push_back(white);
      v_colors.push_back(white);
      v_colors.push_back(white);
      v_normals.push_back(nrm);
      v_normals.push_back(nrm);
      v_normals.push_back(nrm);
      v_textures.push_back(t_coords[1]);
      v_textures.push_back(t_coords[1]);
      v_textures.push_back(t_coords[1]);
    }

}
void cylinder(vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& tex_coords, float radius, float height, int color)
{
  //RGBA colors
  glm::vec4 colors[8] = {
    glm::vec4(0.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 1.0, 1.0, 1.0)
  };

  glm::vec2 t_coords[4] = {
    glm::vec2( 0.0, 0.0),
    glm::vec2( 0.0, 1.0),
    glm::vec2( 1.0, 0.0),
    glm::vec2( 1.0, 1.0)
  };

  for (float i = 0; i <1 ; i+=0.01)
  {
    float theta = i*2.0*PI, nextTheta = (i+0.01)*2.0*PI;
    v_positions.push_back(glm::vec4(radius*cos(theta),-height,radius*sin(theta),1.0));
    v_positions.push_back(glm::vec4(radius*cos(nextTheta),-height,radius*sin(nextTheta),1.0));
    v_positions.push_back(glm::vec4(radius*cos(theta),0,radius*sin(theta),1.0));
    v_positions.push_back(glm::vec4(radius*cos(nextTheta),-height,radius*sin(nextTheta),1.0));
    v_positions.push_back(glm::vec4(radius*cos(nextTheta),0,radius*sin(nextTheta),1.0));
    v_positions.push_back(glm::vec4(radius*cos(theta),0,radius*sin(theta),1.0));

    v_normals.push_back(glm::vec4(radius*cos(theta),0,radius*sin(theta),1.0));
    v_normals.push_back(glm::vec4(radius*cos(nextTheta),0,radius*sin(nextTheta),1.0));
    v_normals.push_back(glm::vec4(radius*cos(theta),-0,radius*sin(theta),1.0));
    v_normals.push_back(glm::vec4(radius*cos(nextTheta),0,radius*sin(nextTheta),1.0));
    v_normals.push_back(glm::vec4(radius*cos(nextTheta),-0,radius*sin(nextTheta),1.0));
    v_normals.push_back(glm::vec4(radius*cos(theta),-0,radius*sin(theta),1.0));

    v_colors.push_back(glm::vec4(colors[color]));
    v_colors.push_back(glm::vec4(colors[color]));
    v_colors.push_back(glm::vec4(colors[color]));
    v_colors.push_back(glm::vec4(colors[color]));
    v_colors.push_back(glm::vec4(colors[color]));
    v_colors.push_back(glm::vec4(colors[color]));

    tex_coords.push_back( glm::vec2(i,1) );
    tex_coords.push_back( glm::vec2(i+0.01,1) );
    tex_coords.push_back( glm::vec2(i,0) );
    tex_coords.push_back( glm::vec2(i+0.01,1) );
    tex_coords.push_back( glm::vec2(i+0.01,0) );
    tex_coords.push_back( glm::vec2(i,0) );
  }
}
void cuboid(vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& tex_coords, float x, float a, float b, float c, int color)
{
  glm::vec4 positions[8] = {
    glm::vec4(a, -b, c, 1.0),//0
    glm::vec4(a, b, c, 1.0),//1
    glm::vec4(x, b, c, 1.0),//2
    glm::vec4(x, -b, c, 1.0),//3
    glm::vec4(a, -b, -c, 1.0),//4
    glm::vec4(a, b, -c, 1.0),//5
    glm::vec4(x, b, -c, 1.0),//6
    glm::vec4(x, -b, -c, 1.0)//7
  };

  //RGBA colors
  glm::vec4 colors[8] = {
    glm::vec4(0.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 1.0, 1.0, 1.0)
  };

  glm::vec2 t_coords[4] = {
    glm::vec2( 0.0, 0.0),
    glm::vec2( 0.0, 1.0),
    glm::vec2( 1.0, 0.0),
    glm::vec2( 1.0, 1.0)
  };

  glm::vec4 xVec(1.0,   0,   0, 1.0),
            yVec(  0, 1.0,   0, 1.0),
            zVec(  0,   0, 1.0, 1.0);

  // glm::vec4 xVec(0,   0,   0, 1.0),
  //           yVec(  0, 0,   0, 1.0),
  //           zVec(  0,   0, 0, 1.0);
// // generate 12 triangles: 36 vertices and 36 colors
  v_positions.push_back(glm::vec4(positions[1]));
  v_positions.push_back(glm::vec4(positions[0]));
  v_positions.push_back(glm::vec4(positions[3]));
  v_normals.push_back(zVec);
  v_normals.push_back(zVec);
  v_normals.push_back(zVec);
  v_positions.push_back(glm::vec4(positions[1]));
  v_positions.push_back(glm::vec4(positions[3]));
  v_positions.push_back(glm::vec4(positions[2]));
  v_normals.push_back(zVec);
  v_normals.push_back(zVec);
  v_normals.push_back(zVec);

  v_positions.push_back(glm::vec4(positions[2]));
  v_positions.push_back(glm::vec4(positions[3]));
  v_positions.push_back(glm::vec4(positions[7]));
  v_normals.push_back(-xVec);
  v_normals.push_back(-xVec);
  v_normals.push_back(-xVec);
  v_positions.push_back(glm::vec4(positions[2]));
  v_positions.push_back(glm::vec4(positions[7]));
  v_positions.push_back(glm::vec4(positions[6]));
  v_normals.push_back(-xVec);
  v_normals.push_back(-xVec);
  v_normals.push_back(-xVec);

  v_positions.push_back(glm::vec4(positions[3]));
  v_positions.push_back(glm::vec4(positions[0]));
  v_positions.push_back(glm::vec4(positions[4]));
  v_normals.push_back(-yVec);
  v_normals.push_back(-yVec);
  v_normals.push_back(-yVec);
  v_positions.push_back(glm::vec4(positions[3]));
  v_positions.push_back(glm::vec4(positions[4]));
  v_positions.push_back(glm::vec4(positions[7]));
  v_normals.push_back(-yVec);
  v_normals.push_back(-yVec);
  v_normals.push_back(-yVec);


  v_positions.push_back(glm::vec4(positions[6]));
  v_positions.push_back(glm::vec4(positions[5]));
  v_positions.push_back(glm::vec4(positions[1]));
  v_normals.push_back(yVec);
  v_normals.push_back(yVec);
  v_normals.push_back(yVec);
  v_positions.push_back(glm::vec4(positions[6]));
  v_positions.push_back(glm::vec4(positions[1]));
  v_positions.push_back(glm::vec4(positions[2]));
  v_normals.push_back(yVec);
  v_normals.push_back(yVec);
  v_normals.push_back(yVec); 


  v_positions.push_back(glm::vec4(positions[4]));
  v_positions.push_back(glm::vec4(positions[5]));
  v_positions.push_back(glm::vec4(positions[6]));
  v_normals.push_back(-zVec);
  v_normals.push_back(-zVec);
  v_normals.push_back(-zVec);
  v_positions.push_back(glm::vec4(positions[4]));
  v_positions.push_back(glm::vec4(positions[6]));
  v_positions.push_back(glm::vec4(positions[7]));
  v_normals.push_back(-zVec);
  v_normals.push_back(-zVec);
  v_normals.push_back(-zVec);

  v_positions.push_back(glm::vec4(positions[5]));
  v_positions.push_back(glm::vec4(positions[4]));
  v_positions.push_back(glm::vec4(positions[0]));
  v_normals.push_back(xVec );
  v_normals.push_back(xVec );
  v_normals.push_back(xVec );
  v_positions.push_back(glm::vec4(positions[5]));
  v_positions.push_back(glm::vec4(positions[0]));
  v_positions.push_back(glm::vec4(positions[1]));
  v_normals.push_back(xVec );
  v_normals.push_back(xVec );
  v_normals.push_back(xVec );

  for (int i = 0; i < 36; ++i)
  {
    v_colors.push_back(glm::vec4(colors[color]));
  }
  for (int i = 0; i < 6; ++i)
  {
    tex_coords.push_back(t_coords[1]);
    tex_coords.push_back(t_coords[0]);
    tex_coords.push_back(t_coords[2]);
    tex_coords.push_back(t_coords[1]);
    tex_coords.push_back(t_coords[2]);
    tex_coords.push_back(t_coords[3]);
  }
}

void plane(vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec2>& tex_coords, float x, float a, float b, float c, int color)
{
  glm::vec4 positions[8] = {
    glm::vec4(a, -b, c, 1.0),
    glm::vec4(a, b, c, 1.0),
    glm::vec4(x, b, c, 1.0),
    glm::vec4(x, -b, c, 1.0),
    glm::vec4(a, -b, -c, 1.0),
    glm::vec4(a, b, -c, 1.0),
    glm::vec4(x, b, -c, 1.0),
    glm::vec4(x, -b, -c, 1.0)
  };

  //RGBA colors
  glm::vec4 colors[8] = {
    glm::vec4(0.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 1.0, 1.0, 1.0)
  };

  glm::vec2 t_coords[4] = {
    glm::vec2( 0.0, 0.0),
    glm::vec2( 0.0, 1.0),
    glm::vec2( 1.0, 0.0),
    glm::vec2( 1.0, 1.0)
  };

  v_positions.push_back(glm::vec4(positions[6]));
  v_positions.push_back(glm::vec4(positions[5]));
  v_positions.push_back(glm::vec4(positions[1]));
  v_positions.push_back(glm::vec4(positions[6]));
  v_positions.push_back(glm::vec4(positions[1]));
  v_positions.push_back(glm::vec4(positions[2]));

  for (int i = 0; i < 6; ++i)
  {
    v_colors.push_back(glm::vec4(colors[color]));
  }
  tex_coords.push_back(t_coords[1]);
  tex_coords.push_back(t_coords[0]);
  tex_coords.push_back(t_coords[2]);
  tex_coords.push_back(t_coords[1]);
  tex_coords.push_back(t_coords[2]);
  tex_coords.push_back(t_coords[3]);
}

void torso(vector<glm::vec4>& v_positions, vector<glm::vec4>& v_colors, vector<glm::vec4>& v_normals, vector<glm::vec2>& v_textures, float radius1, float radius2, float radius3, float height1,float height2, int color)
{
  glm::vec4 p1,p2,p3,p4,p5,p6,n1,n2,n3,n4,n5,n6;
  glm::vec2 t1,t2,t3,t4,t5,t6;
  float x1 = radius1 * 3/2;
  float y1 = radius1;
  float x2 = radius2;
  float y2 = radius3 * 3/2;
  float x3 = radius3;
  float y3 = radius3;

  for (float i = 0; i < 200; ++i)
  {
    float theta=(i*PI)/100,nextTheta=(i+1)*PI/100;
    p1 = glm::vec4(x1 * cos(theta) ,0 , y1 * sin(theta),1);
    p2 = glm::vec4(x1 * cos(nextTheta) ,0 , y1 * sin(nextTheta),1);

    p3 = glm::vec4(x2 * cos(theta) ,height1, y2 * sin(theta),1);
    p4 = glm::vec4(x2 * cos(nextTheta) ,height1, y2 * sin(nextTheta),1);

    p5 = glm::vec4(x3 * cos(theta) ,height2+height1, y2 * sin(theta),1);
    p6 = glm::vec4(x3 * cos(nextTheta) ,height2+height1, y2 * sin(nextTheta),1);

    n1 = glm::vec4(x1 * cos(theta) ,radius1*(radius2-radius1)/height1 , y1 * sin(theta),1);
    n2 = glm::vec4(x1 * cos(nextTheta) ,radius1*(radius2-radius1)/height1 , y1 * sin(nextTheta),1);

    //n3 = glm::vec4(x2 * cos(theta) ,0, y2 * sin(theta),1);
    //n4 = glm::vec4(x2 * cos(nextTheta) ,0, y2 * sin(nextTheta),1);

    n5 = glm::vec4(x3 * cos(theta) ,radius3*(radius2-radius1)/height1, y2 * sin(theta),1);
    n6 = glm::vec4(x3 * cos(nextTheta) ,radius3*(radius2-radius1)/height1, y2 * sin(nextTheta),1);

    t1 = glm::vec2(i/200.0,0);
    t2 = glm::vec2((i+1)/200.0,0);

    t3 = glm::vec2(i/200.0,height1/(height1+height2));
    t4 = glm::vec2((i+1)/200.0,height1/(height1+height2));

    t5 = glm::vec2(i/200.0,1);
    t6 = glm::vec2((i+1)/200.0,1);
    v_colors.push_back(white);    v_colors.push_back(white);    v_colors.push_back(white);
    v_positions.push_back(p1);     v_positions.push_back(p2);     v_positions.push_back(p3); 
    v_normals.push_back(n1);    v_normals.push_back(n2);    v_normals.push_back(n1);
    v_textures.push_back(t1);    v_textures.push_back(t2);    v_textures.push_back(t3);


    v_colors.push_back(white);    v_colors.push_back(white);    v_colors.push_back(white);
    v_positions.push_back(p2);     v_positions.push_back(p3);     v_positions.push_back(p4); 
    v_normals.push_back(n2);    v_normals.push_back(n1);    v_normals.push_back(n2);
    v_textures.push_back(t2);    v_textures.push_back(t3);    v_textures.push_back(t4);


    v_colors.push_back(white);    v_colors.push_back(white);    v_colors.push_back(white);
    v_positions.push_back(p3);     v_positions.push_back(p4);     v_positions.push_back(p5); 
    v_normals.push_back(n5);    v_normals.push_back(n6);    v_normals.push_back(n5);
    v_textures.push_back(t3);    v_textures.push_back(t4);    v_textures.push_back(t5);


    v_colors.push_back(white);    v_colors.push_back(white);    v_colors.push_back(white);
    v_positions.push_back(p4);     v_positions.push_back(p5);     v_positions.push_back(p6); 
    v_normals.push_back(n6);    v_normals.push_back(n5);    v_normals.push_back(n6);
    v_textures.push_back(t4);    v_textures.push_back(t5);    v_textures.push_back(t6);

  }
}