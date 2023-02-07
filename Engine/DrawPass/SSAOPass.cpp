#include "SSAOPass.hpp"

#include "Interface/IApplication.hpp"

// @TODO: remove
extern void R_DrawQuad();

void SSAOPass::Draw( Frame& frame )
{
    unused( frame );

    auto PSO = m_pPipelineStateManager->GetPipelineState( "SSAO" );
    m_pGraphicsManager->SetPipelineState( PSO );

    auto pApp = m_pPipelineStateManager->GetAppPointer();
    uint32_t width = 0, height = 0;
    pApp->GetFramebufferSize( width, height );
    glViewport( 0, 0, width, height );

    R_DrawQuad();
}