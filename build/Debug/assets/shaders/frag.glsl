#version 330 core

in vec2 vsTexCoord;

out vec4 FragColor;

uniform sampler2D uTexture;

void main() {
    vec4 texColor = texture(uTexture, vsTexCoord);
    
    // // If the pixel is supposed to be transparent, paint it hot pink
    // if (texColor.a < 0.5) {
    //     FragColor = vec4(1.0, 0.0, 1.0, 1.0); // Hot Pink
    // } else {
    //     // If it's opaque, paint it neon green
    //     FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Neon Green
    // }
    FragColor = texColor;
}
