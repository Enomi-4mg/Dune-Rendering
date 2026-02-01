#version 150

uniform sampler2D normalMap;
uniform vec3 lightDir; // C++から渡す太陽の向き

in vec2 v_texCoord;
out vec4 outputColor;

void main() {
    vec3 resNormal = texture(normalMap, v_texCoord).rgb;
    // [0, 1] -> [-1, 1] への変換が C++ 側の setColor と一致しているか再確認
    vec3 normal = normalize(resNormal * 2.0 - 1.0);

    // 太陽の向き（lightDir）が正規化されているか確認
    vec3 L = normalize(lightDir);
    float diffuse = max(dot(normal, L), 0.0);

    // 砂の色を少し落としてみる (0.9 -> 0.7)
    vec3 sandColor = vec3(0.7, 0.6, 0.4); 
    
    // 環境光（Ambient）が強すぎないかチェック
    vec3 viewDir = normalize(vec3(0, 0, 1)); // 簡易的な視線方向
    vec3 halfDir = normalize(L + viewDir);
    float spec = pow(max(dot(normal, halfDir), 0.0), 32.0); // 32は光沢の鋭さ
    outputColor = vec4(sandColor * (diffuse + ambient) + vec3(spec * 0.2), 1.0);
}