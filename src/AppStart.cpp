#include "App.hpp"

#include "Util/Logger.hpp"

void App::Start() {
    LOG_TRACE("Start");

    std::vector<std::string> GiraffeImages;
    GiraffeImages.reserve(12);
    for (int i = 0; i < 12; ++i) {
        GiraffeImages.emplace_back(GA_RESOURCE_DIR"/Image/Character/hero00" + std::to_string(i +22) + ".png");
    }

    m_Hero = std::make_shared<AnimatedCharacter>(GiraffeImages);
    m_Hero->SetPosition({197.5f, -3.5f});
    m_Hero->SetZIndex(50);
    m_Hero->SetLooping(true);
    m_Root.AddChild(m_Hero);



    m_PRM = std::make_shared<PhaseResourceManger>();
    m_Root.AddChildren(m_PRM->GetChildren());


    m_CurrentState = State::UPDATE;
}
