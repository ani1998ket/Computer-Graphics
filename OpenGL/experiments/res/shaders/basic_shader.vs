#version 330 core

layout( location = 0) in vec4 i_position;
layout( location = 1) in vec4 i_color;

out vec4 v_color;

void main(){
    gl_Position = i_position;
    v_color = i_color;
}