#include "framework.hpp"

class Presenter : public Framework {
    void OnCreate() override
    {
        auto bgVS = tga::loadShader("shaders/background_vert.spv", tga::ShaderType::vertex, tgai);
        auto bgFS = tga::loadShader("shaders/background_frag.spv", tga::ShaderType::fragment, tgai);
        backgroundPass = tgai->createRenderPass(
            {{bgVS, bgFS},
             frameworkWindow,
             tga::ClearOperation::none,
             {},
             {},
             {{/* Three uniform Buffers for the System Input*/
               {tga::BindingType::uniformBuffer, tga::BindingType::uniformBuffer, tga::BindingType::uniformBuffer}}}});
        systemInputSet = makeSystemInputSet(backgroundPass);

        // Shaders get backed into the renderpass, we don't need the modules anymore, so free them
        tgai->free(bgVS);
        tgai->free(bgFS);
    }

    void OnFixedUpdate() override {}

    void OnUpdate(uint32_t backbufferIndex) override
    {
        /*Update Data here*/
        tgai->beginCommandBuffer(cmdBuffer);
        tgai->setRenderPass(backgroundPass, backbufferIndex);
        tgai->bindInputSet(systemInputSet);
        tgai->draw(3, 0);

        cmdBuffer = tgai->endCommandBuffer();
        tgai->execute(cmdBuffer);
    }
    void OnDestroy() override {}

    tga::CommandBuffer cmdBuffer;
    tga::InputSet systemInputSet;
    tga::RenderPass backgroundPass;
};

int main()
{
    try {
        Presenter presenter;
        presenter.run({0, 0}, tga::PresentMode::immediate);
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}
