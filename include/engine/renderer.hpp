#ifndef _INTERNAL_RENDERER_H
#define _INTERNAL_RENDERER_H


namespace gfx
{
    class Renderer
    /*
    This class is not exposed as an interface as it is passed to all Draw(gfx::Renderer* gfx);
    */
    {
    public:
        Renderer();
        ~Renderer();

        int Init();
        void Exit();

    }
}

#endif
