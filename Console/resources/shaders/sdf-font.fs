#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;  // Coordenadas de textura para cada fragmento
in vec4 fragColor;     // Cor final do fragmento (usada para o texto)

// Input uniform values
uniform sampler2D texture0;  // Textura do SDF (contendo a fonte)
uniform vec4 colDiffuse;     // Cor difusa (geralmente branca para texto)

// Output fragment color
out vec4 finalColor;   // Cor final do fragmento (após o processamento do shader)

// Custom variables
uniform float smoothing; // Controla a suavização das bordas do texto

void main()
{
    // Fetch texel color from the SDF texture (using alpha channel for distance field)
    float distanceFromOutline = texture(texture0, fragTexCoord).a - 0.5;

    // Compute how much the distance is changing per fragment (using derivatives)
    float distanceChangePerFragment = length(vec2(dFdx(distanceFromOutline), dFdy(distanceFromOutline)));

    // Apply smoothstep to create smooth borders for the SDF effect
    // Adjust the smoothing factor based on the distance change
    float alpha = smoothstep(-smoothing - distanceChangePerFragment, smoothing + distanceChangePerFragment, distanceFromOutline);

    // Calculate final fragment color with alpha blending (transparency)
    finalColor = vec4(colDiffuse.rgb, colDiffuse.a * alpha);
}
