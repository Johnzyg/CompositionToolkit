#include "pch.h"

using namespace winrt;

using namespace Windows;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;
using namespace Microsoft::UI::Composition::Toolkit;

struct App : implements<App, IFrameworkViewSource, IFrameworkView>
{
    CompositionTarget m_target{ nullptr };

    IFrameworkView CreateView()
    {
        return *this;
    }

    void Initialize(CoreApplicationView const&)
    {
    }

    void SetWindow(CoreWindow const&)
    {
        Compositor compositor;
        ContainerVisual root = compositor.CreateContainerVisual();
        m_target = compositor.CreateTargetForCurrentView();
        m_target.Root(root);

        Uri localUri(L"ms-appx:///Assets/StoreLogo.png");
        auto imageFactory = CompositionImageFactory::CreateCompositionImageFactory(compositor);

        CompositionImageOptions options;
        options.DecodeWidth(400);
        options.DecodeHeight(400);

        auto image = imageFactory.CreateImageFromUri(localUri, options);
        auto visual = compositor.CreateSpriteVisual();
        visual.Size({ 400.0f, 400.0f });
        visual.Brush(compositor.CreateSurfaceBrush(image.Surface()));
        root.Children().InsertAtTop(visual);

        image.ImageLoaded([=](CompositionImage const&, CompositionImageLoadStatus status)
        {
            if (status != CompositionImageLoadStatus::Success)
            {
                visual.Brush(compositor.CreateColorBrush(Colors::Red()));
            }
        });
    }

    void Load(hstring const&)
    {
    }

    void Run()
    {
        CoreWindow window = CoreWindow::GetForCurrentThread();
        window.Activate();

        CoreDispatcher dispatcher = window.Dispatcher();
        dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
    }

    void Uninitialize()
    {
    }
};

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    CoreApplication::Run(App());
}
