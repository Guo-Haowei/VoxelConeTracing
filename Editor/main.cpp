#include "imgui/imgui.h"

#include "Engine/Base/Asserts.h"
#include "Engine/Base/Logger.h"

#include "Engine/Core/dvar_api.h"
#include "Engine/Core/FileManager.h"
#include "Engine/Core/com_misc.h"
#include "Engine/Core/editor.h"
#include "Engine/Core/WindowManager.h"

#include "Engine/Graphics/GraphicsManager.hpp"
#include "Engine/Graphics/PipelineStateManager.hpp"

static int app_main( int argc, const char** argv )
{
    bool ok = true;

    ok = ok && Com_RegisterDvars();
    ok = ok && dvar_process_from_cmdline( argc - 1, argv + 1 );

    ok = ok && manager_init( g_fileMgr );

    ok = ok && Com_LoadScene();
    ok = ok && Com_ImGuiInit();

    ok = ok && manager_init( g_wndMgr );
    ok = ok && g_gfxMgr->Initialize();

    // TODO: refactor
    ok = ok && g_pPipelineStateManager->Initialize();

    g_gfxMgr->InitializeGeometries( Com_GetScene() );

    while ( !g_wndMgr->ShouldClose() ) {
        g_wndMgr->NewFrame();

        Com_UpdateWorld();
        EditorSetup();

        g_gfxMgr->Tick();

        Com_GetScene().dirty = false;
    }

    g_pPipelineStateManager->Finalize();

    g_gfxMgr->Finalize();
    manager_deinit( g_wndMgr );
    ImGui::DestroyContext();

    manager_deinit( g_fileMgr );

    return ok ? 0 : 1;
}

int main( int argc, const char** argv )
{
    return app_main( argc, argv );
}
