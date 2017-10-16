using System;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using Windows.UI.Composition;
using Microsoft.UI.Composition.Toolkit;
using System.Numerics;
using Windows.UI;

class App : IFrameworkViewSource, IFrameworkView
{
    CompositionTarget m_target;

    static void Main()
    {
        CoreApplication.Run(new App());
    }

    public IFrameworkView CreateView()
    {
        return this;
    }

    public void Initialize(CoreApplicationView applicationView)
    {
    }

    public void SetWindow(CoreWindow window)
    {
        Compositor compositor = new Compositor();
        ContainerVisual root = compositor.CreateContainerVisual();
        m_target = compositor.CreateTargetForCurrentView();
        m_target.Root = root;

        Uri localUri = new Uri("ms-appx:///Assets/StoreLogo.png");
        var imageFactory = CompositionImageFactory.CreateCompositionImageFactory(compositor);

        CompositionImageOptions options = new CompositionImageOptions()
        {
            DecodeWidth = 400,
            DecodeHeight = 400,
        };

        var image = imageFactory.CreateImageFromUri(localUri, options);
        var visual = compositor.CreateSpriteVisual();
        visual.Size = new Vector2(400.0f, 400.0f);
        visual.Brush = compositor.CreateSurfaceBrush(image.Surface);
        root.Children.InsertAtTop(visual);

        image.ImageLoaded += (CompositionImage sender, CompositionImageLoadStatus status) =>
        {
            if (status != CompositionImageLoadStatus.Success)
            {
                visual.Brush = compositor.CreateColorBrush(Colors.Red);
            }
        };
    }

    public void Load(string entryPoint)
    {
    }

    public void Run()
    {
        CoreWindow window = CoreWindow.GetForCurrentThread();
        window.Activate();

        CoreDispatcher dispatcher = window.Dispatcher;
        dispatcher.ProcessEvents(CoreProcessEventsOption.ProcessUntilQuit);
    }

    public void Uninitialize()
    {
    }
}
