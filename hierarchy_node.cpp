#include "hierarchy_node.hpp"

#include <iostream>

extern GLuint vPosition,vColor,vNormal,texCoord,uModelViewMatrix,normalMatrix,viewMatrix,Light,spot;
extern glm::mat3 normal_matrix;
extern glm::mat4 view_matrix;
extern std::vector<glm::mat4> matrixStack;
extern int light,spotlight;

namespace csX75
{

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec4* a_normals, glm::vec2* tex_coords, int v_size, int c_size, int n_size, int t_size, GLuint tex){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		texture=tex;
		// initialize vao and vbo of the object;


		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + n_size + t_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size, n_size , a_normals );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + n_size, t_size , tex_coords );

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		glEnableVertexAttribArray( vNormal );
		glVertexAttribPointer( vNormal, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));

		//Textures
	  glEnableVertexAttribArray( texCoord );
	  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size + n_size) );

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}

	HNode::HNode(HNode* a_parent, GLuint num_v, glm::vec4* a_vertices, glm::vec4* a_colours, glm::vec2* tex_coords, int v_size, int c_size, int t_size, GLuint tex){

		num_vertices = num_v;
		vertex_buffer_size = v_size;
		color_buffer_size = c_size;
		texture=tex;
		// initialize vao and vbo of the object;

		//Ask GL for a Vertex Attribute Objects (vao)
		glGenVertexArrays (1, &vao);
		//Ask GL for aVertex Buffer Object (vbo)
		glGenBuffers (1, &vbo);

		//bind them
		glBindVertexArray (vao);
		glBindBuffer (GL_ARRAY_BUFFER, vbo);

		glBufferData (GL_ARRAY_BUFFER, vertex_buffer_size + color_buffer_size + t_size, NULL, GL_STATIC_DRAW);
		glBufferSubData( GL_ARRAY_BUFFER, 0, vertex_buffer_size, a_vertices );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size, color_buffer_size, a_colours );
		glBufferSubData( GL_ARRAY_BUFFER, vertex_buffer_size+color_buffer_size, t_size, tex_coords);

		//setup the vertex array as per the shader
		glEnableVertexAttribArray( vPosition );
		glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

		glEnableVertexAttribArray( vColor );
		glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size));

		//Textures
	  glEnableVertexAttribArray( texCoord );
	  glVertexAttribPointer( texCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vertex_buffer_size + color_buffer_size) );

		// set parent

		if(a_parent == NULL){
			parent = NULL;
		}
		else{
			parent = a_parent;
			parent->add_child(this);
		}

		//initial parameters are set to 0;

		tx=ty=tz=rx=ry=rz=0;

		update_matrices();
	}


	void HNode::update_matrices(){

		rotation = glm::rotate(glm::mat4(1.0f), glm::radians(rx), glm::vec3(1.0f,0.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(ry), glm::vec3(0.0f,1.0f,0.0f));
		rotation = glm::rotate(rotation, glm::radians(rz), glm::vec3(0.0f,0.0f,1.0f));

		translation = glm::translate(glm::mat4(1.0f),glm::vec3(tx,ty,tz));


	}

	void HNode::add_child(HNode* a_child){
		children.push_back(a_child);

	}

	void HNode::change_parameters(GLfloat atx, GLfloat aty, GLfloat atz, GLfloat arx, GLfloat ary, GLfloat arz){
		tx = atx;
		ty = aty;
		tz = atz;
		rx = arx;
		ry = ary;
		rz = arz;

		update_matrices();
	}

	void HNode::render(){

		//matrixStack multiply
		glm::mat4* ms_mult = multiply_stack(matrixStack);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, glm::value_ptr(view_matrix));
		glm::mat4 model_matrix = rotation*translation;
		glUniformMatrix4fv(uModelViewMatrix, 1, GL_FALSE, glm::value_ptr(*ms_mult));
		normal_matrix = glm::mat3(glm::transpose (glm::inverse(glm::mat4(glm::inverse(view_matrix) * *ms_mult))));
  	glUniformMatrix3fv(normalMatrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  	glUniform1i(Light,light);
  	glUniform1i(spot,spotlight);
		glBindVertexArray (vao);
		glDrawArrays(GL_TRIANGLES, 0, num_vertices);

		// for memory 
		delete ms_mult;

	}

	void HNode::render_tree(){
		
		matrixStack.push_back(translation);
		matrixStack.push_back(rotation);

		render();
		for(int i=0;i<children.size();i++){
			children[i]->render_tree();
		}
		matrixStack.pop_back();
		matrixStack.pop_back();

	}

	void HNode::inc_rx(){
		rx++;
		update_matrices();
	}

	void HNode::inc_ry(){
		ry++;
		update_matrices();
	}

	void HNode::inc_rz(){
		rz++;
		update_matrices();
	}

	void HNode::dec_rx(){
		rx--;
		update_matrices();
	}

	void HNode::dec_ry(){
		ry--;
		update_matrices();
	}

	void HNode::dec_rz(){
		rz--;
		update_matrices();
	}


	glm::mat4* multiply_stack(std::vector<glm::mat4> matStack){
		glm::mat4* mult;
		mult = new glm::mat4(1.0f);
	
		for(int i=0;i<matStack.size();i++){
			*mult = (*mult) * matStack[i];
		}	

		return mult;
	}

}