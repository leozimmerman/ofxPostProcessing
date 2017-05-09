/*
 *  InversePass.h
 *
 *  Copyright (c) 2017, satcy, http://satcy.net
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "InversePass.h"
#include "ofMain.h"

namespace itg
{
    InversePass::InversePass(const ofVec2f& aspect, bool arb, float amount) :
        amount(amount), RenderPass(aspect, arb, "InversePass")
    {
        
        string fragShaderSrc = STRINGIFY(
                                         uniform SAMPLER_TYPE tDiffuse;
                                         uniform float amount;
                        
                                         void main() {
                                         vec2 vUv = gl_TexCoord[0].st;
                                         vec4 ca = TEXTURE_FN(tDiffuse, vUv);
                                         vec4 cb = vec4(1.0 - ca.r, 1.0 - ca.g, 1.0 - ca.b, ca.a);
                                         gl_FragColor = ca * (1.0 - amount) + cb * amount;
                                         
                                         }
        );
        
        ostringstream oss;
        oss << "#version 120" << endl;
        if (arb)
        {
            oss << "#define SAMPLER_TYPE sampler2DRect" << endl;
            oss << "#define TEXTURE_FN texture2DRect" << endl;
            oss << "#extension GL_ARB_texture_rectangle : enable" << endl;
            oss << fragShaderSrc;
        }
        else
        {
            oss << "#define SAMPLER_TYPE sampler2D" << endl;
            oss << "#define TEXTURE_FN texture2D" << endl;
            oss << fragShaderSrc;
        }
    
        shader.setupShaderFromSource(GL_FRAGMENT_SHADER, oss.str());
        shader.linkProgram();
        
    }
    

    void InversePass::render(ofFbo& readFbo, ofFbo& writeFbo)
    {
        writeFbo.begin();
        
        shader.begin();
        
        shader.setUniformTexture("tDiffuse", readFbo.getTexture(), 0);
        shader.setUniform1f("amount", amount);
        
        texturedQuad(0, 0, writeFbo.getWidth(), writeFbo.getHeight());
        
        shader.end();
        writeFbo.end();
    }
}