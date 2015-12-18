#include "gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot,c_zpos;
extern bool enable_perspective;
extern int light,spotlight;
extern csX75::HNode* node0, *node1, *node2, *node3, *node21, *node22, *node23, *node31, *node32, *node33, *node41, *node42, *node43, *node51, *node52, *node53, *curr_node;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GL_TRUE);
    // else if (key == GLFW_KEY_9 && action == GLFW_PRESS && model==true)
    //   curr_node = node1; 
    else if (key == GLFW_KEY_9 && action == GLFW_PRESS)
      curr_node = node1;  
    else if (key == GLFW_KEY_0 && action == GLFW_PRESS)
      curr_node = node2; 
    else if (key == GLFW_KEY_C && action == GLFW_PRESS)
      curr_node = node3; 
    else if (key == GLFW_KEY_1 && action == GLFW_PRESS)
      curr_node = node21;  
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
      curr_node = node22;  
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
      curr_node = node31;  
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
      curr_node = node32; 
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
      curr_node = node41;  
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
      curr_node = node42; 
    else if (key == GLFW_KEY_7 && action == GLFW_PRESS)
      curr_node = node51;  
    else if (key == GLFW_KEY_8 && action == GLFW_PRESS)
      curr_node = node52; 
    else if (key == GLFW_KEY_LEFT && curr_node!=node22  && curr_node!=node32  && curr_node!=node42  && curr_node!=node52)
    {
      if (curr_node==node21 || curr_node==node31)
      {
        if (curr_node->ry > -90.0)
        {
          curr_node->dec_ry();
        }
      }
      else
        curr_node->dec_ry();
    }  
    else if (key == GLFW_KEY_RIGHT && curr_node!=node22  && curr_node!=node32  && curr_node!=node42  && curr_node!=node52)
    {
      if (curr_node==node21 || curr_node==node31)
      {
        if (curr_node->ry < 90.0)
        {
          curr_node->inc_ry();
        }
      }
      else
        curr_node->inc_ry();
    }  
    else if (key == GLFW_KEY_UP && curr_node!=node3) 
    {
      if (curr_node == node51 || curr_node == node41)
      {
        if (curr_node->rx > -90.0)
        {
          curr_node->dec_rx();
        }
      }
      else if (curr_node == node22 || curr_node == node32 || curr_node == node42 || curr_node == node52)
      {
        if (curr_node->rx > -90.0)
        {
          curr_node->dec_rx();
        }
      }
      else
        curr_node->dec_rx();
    }
    else if (key == GLFW_KEY_DOWN && curr_node!=node3)
    {
      if (curr_node == node51 || curr_node == node41 || curr_node == node22 || curr_node == node32 || curr_node == node42 || curr_node == node52)
      {
        if (curr_node->rx < 90.0)
        {
          curr_node->inc_rx();
        }
      }
      else
        curr_node->inc_rx();
    }
    else if (key == GLFW_KEY_PAGE_UP && curr_node!=node22  && curr_node!=node32  && curr_node!=node42  && curr_node!=node52 && curr_node!=node3)
    {
      if (curr_node->rz > -180.0 && curr_node==node31)
      {
        curr_node->dec_rz();
      }
      if (curr_node->rz > -90.0 && (curr_node==node41 || curr_node==node51 || curr_node==node2))
      {
        curr_node->dec_rz();
      }
      else if ((curr_node->rz > 0.0 || curr_node==node1) && curr_node!=node31)
      {
        curr_node->dec_rz();
      }
    }  
    else if (key == GLFW_KEY_PAGE_DOWN && curr_node!=node22  && curr_node!=node32  && curr_node!=node42  && curr_node!=node52 && curr_node!=node3)
    {
      if (curr_node->rz < 0.0 && curr_node==node31)
      {
        curr_node->inc_rz();
      }
      if (curr_node->rz < 90.0 && (curr_node==node41 || curr_node==node51 || curr_node==node2))
      {
        curr_node->inc_rz();
      }
      else if ((curr_node->rz < 180.0 || curr_node==node1) && !(curr_node==node41 || curr_node==node51 || curr_node==node2 || curr_node==node31))
      {
        curr_node->inc_rz();
      }
    } 
    else if (key == GLFW_KEY_P && action == GLFW_PRESS)
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A)
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D)
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W)
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S)
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q)
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E)
      c_zrot += 1.0;
    else if (key == GLFW_KEY_Z)
      c_zpos -= 0.1;
    else if (key == GLFW_KEY_X)
      c_zpos += 0.1;
    else if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS)
    {
      if (light<2)
      {
        light += 1;
      }
    }  
    else if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS)
    {
      if (light>0)
      {
        light -= 1;
      }
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
      spotlight = (spotlight==1?0:1); 
  }
};  
  


