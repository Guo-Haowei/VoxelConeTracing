#pragma once
#include <vector>
#include "Interface/IApplication.hpp"
#include "Interface/IAssetLoader.hpp"
#include "Interface/IGraphicsManager.hpp"
#include "Interface/IPipelineStateManager.hpp"
#include "Interface/ISceneManager.hpp"
#include "Interface/IGameLogic.hpp"

class BaseApplication : public IApplication {
public:
    BaseApplication() = default;
    ~BaseApplication() override = default;

    virtual bool ProcessCommandLine( int argc, const char** argv ) override;
    virtual bool Initialize() override;
    virtual void Finalize();

    virtual void Tick();

    virtual bool ShouldQuit() override;
    virtual void RequestQuit() override { m_bShouldQuit = true; }

    void GetFramebufferSize( uint32_t&, uint32_t& ) override {}

    bool CreateMainWindow() override { return false; }
    void* GetMainWindowHandler() override { return nullptr; }

    void RegisterManagerModule( IAssetLoader* mgr );
    void RegisterManagerModule( ISceneManager* mgr );
    void RegisterManagerModule( IGraphicsManager* mgr );
    void RegisterManagerModule( IPipelineStateManager* mgr );
    void RegisterManagerModule( IGameLogic* mgr );

    IAssetLoader* GetAssetLoader()
    {
        return m_pAssetLoader;
    }

    ISceneManager* GetSceneManager()
    {
        return m_pSceneManager;
    }

    IGraphicsManager* GetGraphicsManager()
    {
        return m_pGraphicsManager;
    }

    IPipelineStateManager* GetPipelineStateManager()
    {
        return m_pPipelineStateManager;
    }

    IGameLogic* GetGameLogic()
    {
        return m_pGameLogic;
    }

protected:
    // Flag if need quit the main loop of the application
    bool m_bShouldQuit = false;

    IAssetLoader* m_pAssetLoader = nullptr;
    ISceneManager* m_pSceneManager = nullptr;
    IGraphicsManager* m_pGraphicsManager = nullptr;
    IPipelineStateManager* m_pPipelineStateManager = nullptr;
    IGameLogic* m_pGameLogic = nullptr;

private:
    std::vector<IRuntimeModule*> m_runtimeModules;
};