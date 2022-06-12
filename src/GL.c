#include <GL.h>
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define _GL_LOADER_PLATFORM_WINDOWS
#elif defined(__unix__)
    #define _GL_LOADER_PLATFORM_UNIX
    #if defined(__linux__)
        #define _GL_LOADER_PLATFORM_LINUX
    #else
        #error Your platform is not supported
    #endif
#elif
    #error Your platform is not supported
#endif


static void* (*getProcAddressPtr)(const char*);
#ifdef _GL_LOADER_PLATFORM_WINDOWS
#ifndef _WINDOWS_
    #undef APIENTRY
#endif
#include <windows.h>
static HMODULE libGL;
static int open_gl(void) {
    libGL = LoadLibraryW(L"opengl32.dll");
    if(libGL != NULL) {
        void (* tmp)(void);
        getProcAddressPtr = (void*(*)(const char*)) GetProcAddress(libGL, "wglGetProcAddress");
        return getProcAddressPtr != NULL;
    }
    return 0;
}
#else // Unix
#include <dlfcn.h>
static void* libGL;
static int open_gl(void) {
    static const char *NAMES[] = {"libGL.so.1", "libGL.so"};
    for(int i = 0; i < (sizeof(NAMES) / sizeof(NAMES[0])); i++) {
        libGL = dlopen(NAMES[i], RTLD_NOW | RTLD_GLOBAL);
        if(libGL != NULL) {
            getProcAddressPtr = (void*(*)(const char*)) dlsym(libGL, "glXGetProcAddressARB");
            return getProcAddressPtr != NULL;
        }
    }
    return 0;
}
#endif

// Close
#ifdef _GL_LOADER_PLATFORM_WINDOWS
static void close_gl(void) {
    if(libGL != NULL) {
        FreeLibrary(libGL);
        libGL = NULL;
    }
}
#else //Unix
static void close_gl(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}
#endif

// Loader
static void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;

    if(getProcAddressPtr != NULL) {
        result = getProcAddressPtr(namez);
    }
    if(result == NULL) {
#ifdef _GL_LOADER_PLATFORM_WINDOWS
        result = (void*)GetProcAddress((HMODULE) libGL, namez);
#else
        result = dlsym(libGL, namez);
#endif
    }

    return result;
}


typedef void (APIENTRY *PFNGLACCUMPROC)(GLenum op, GLfloat value);
PFNGLACCUMPROC _gl_loader_glaccum = NULL;
typedef void (APIENTRY *PFNGLACTIVESHADERPROGRAMPROC)(GLuint pipeline, GLuint program);
PFNGLACTIVESHADERPROGRAMPROC _gl_loader_glactiveshaderprogram = NULL;
typedef void (APIENTRY *PFNGLACTIVETEXTUREPROC)(GLenum texture);
PFNGLACTIVETEXTUREPROC _gl_loader_glactivetexture = NULL;
typedef void (APIENTRY *PFNGLALPHAFUNCPROC)(GLenum func, GLfloat ref);
PFNGLALPHAFUNCPROC _gl_loader_glalphafunc = NULL;
typedef GLboolean (APIENTRY *PFNGLARETEXTURESRESIDENTPROC)(GLsizei n, const GLuint * textures, GLboolean * residences);
PFNGLARETEXTURESRESIDENTPROC _gl_loader_glaretexturesresident = NULL;
typedef void (APIENTRY *PFNGLARRAYELEMENTPROC)(GLint i);
PFNGLARRAYELEMENTPROC _gl_loader_glarrayelement = NULL;
typedef void (APIENTRY *PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLATTACHSHADERPROC _gl_loader_glattachshader = NULL;
typedef void (APIENTRY *PFNGLBEGINPROC)(GLenum mode);
PFNGLBEGINPROC _gl_loader_glbegin = NULL;
typedef void (APIENTRY *PFNGLBEGINCONDITIONALRENDERPROC)(GLuint id, GLenum mode);
PFNGLBEGINCONDITIONALRENDERPROC _gl_loader_glbeginconditionalrender = NULL;
typedef void (APIENTRY *PFNGLBEGINQUERYPROC)(GLenum target, GLuint id);
PFNGLBEGINQUERYPROC _gl_loader_glbeginquery = NULL;
typedef void (APIENTRY *PFNGLBEGINQUERYINDEXEDPROC)(GLenum target, GLuint index, GLuint id);
PFNGLBEGINQUERYINDEXEDPROC _gl_loader_glbeginqueryindexed = NULL;
typedef void (APIENTRY *PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum primitiveMode);
PFNGLBEGINTRANSFORMFEEDBACKPROC _gl_loader_glbegintransformfeedback = NULL;
typedef void (APIENTRY *PFNGLBINDATTRIBLOCATIONPROC)(GLuint program, GLuint index, const GLchar * name);
PFNGLBINDATTRIBLOCATIONPROC _gl_loader_glbindattriblocation = NULL;
typedef void (APIENTRY *PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
PFNGLBINDBUFFERPROC _gl_loader_glbindbuffer = NULL;
typedef void (APIENTRY *PFNGLBINDBUFFERBASEPROC)(GLenum target, GLuint index, GLuint buffer);
PFNGLBINDBUFFERBASEPROC _gl_loader_glbindbufferbase = NULL;
typedef void (APIENTRY *PFNGLBINDBUFFERRANGEPROC)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
PFNGLBINDBUFFERRANGEPROC _gl_loader_glbindbufferrange = NULL;
typedef void (APIENTRY *PFNGLBINDBUFFERSBASEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers);
PFNGLBINDBUFFERSBASEPROC _gl_loader_glbindbuffersbase = NULL;
typedef void (APIENTRY *PFNGLBINDBUFFERSRANGEPROC)(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes);
PFNGLBINDBUFFERSRANGEPROC _gl_loader_glbindbuffersrange = NULL;
typedef void (APIENTRY *PFNGLBINDFRAGDATALOCATIONPROC)(GLuint program, GLuint color, const GLchar * name);
PFNGLBINDFRAGDATALOCATIONPROC _gl_loader_glbindfragdatalocation = NULL;
typedef void (APIENTRY *PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name);
PFNGLBINDFRAGDATALOCATIONINDEXEDPROC _gl_loader_glbindfragdatalocationindexed = NULL;
typedef void (APIENTRY *PFNGLBINDFRAMEBUFFERPROC)(GLenum target, GLuint framebuffer);
PFNGLBINDFRAMEBUFFERPROC _gl_loader_glbindframebuffer = NULL;
typedef void (APIENTRY *PFNGLBINDIMAGETEXTUREPROC)(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format);
PFNGLBINDIMAGETEXTUREPROC _gl_loader_glbindimagetexture = NULL;
typedef void (APIENTRY *PFNGLBINDIMAGETEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
PFNGLBINDIMAGETEXTURESPROC _gl_loader_glbindimagetextures = NULL;
typedef void (APIENTRY *PFNGLBINDPROGRAMPIPELINEPROC)(GLuint pipeline);
PFNGLBINDPROGRAMPIPELINEPROC _gl_loader_glbindprogrampipeline = NULL;
typedef void (APIENTRY *PFNGLBINDRENDERBUFFERPROC)(GLenum target, GLuint renderbuffer);
PFNGLBINDRENDERBUFFERPROC _gl_loader_glbindrenderbuffer = NULL;
typedef void (APIENTRY *PFNGLBINDSAMPLERPROC)(GLuint unit, GLuint sampler);
PFNGLBINDSAMPLERPROC _gl_loader_glbindsampler = NULL;
typedef void (APIENTRY *PFNGLBINDSAMPLERSPROC)(GLuint first, GLsizei count, const GLuint * samplers);
PFNGLBINDSAMPLERSPROC _gl_loader_glbindsamplers = NULL;
typedef void (APIENTRY *PFNGLBINDTEXTUREPROC)(GLenum target, GLuint texture);
PFNGLBINDTEXTUREPROC _gl_loader_glbindtexture = NULL;
typedef void (APIENTRY *PFNGLBINDTEXTUREUNITPROC)(GLuint unit, GLuint texture);
PFNGLBINDTEXTUREUNITPROC _gl_loader_glbindtextureunit = NULL;
typedef void (APIENTRY *PFNGLBINDTEXTURESPROC)(GLuint first, GLsizei count, const GLuint * textures);
PFNGLBINDTEXTURESPROC _gl_loader_glbindtextures = NULL;
typedef void (APIENTRY *PFNGLBINDTRANSFORMFEEDBACKPROC)(GLenum target, GLuint id);
PFNGLBINDTRANSFORMFEEDBACKPROC _gl_loader_glbindtransformfeedback = NULL;
typedef void (APIENTRY *PFNGLBINDVERTEXARRAYPROC)(GLuint array);
PFNGLBINDVERTEXARRAYPROC _gl_loader_glbindvertexarray = NULL;
typedef void (APIENTRY *PFNGLBINDVERTEXBUFFERPROC)(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
PFNGLBINDVERTEXBUFFERPROC _gl_loader_glbindvertexbuffer = NULL;
typedef void (APIENTRY *PFNGLBINDVERTEXBUFFERSPROC)(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
PFNGLBINDVERTEXBUFFERSPROC _gl_loader_glbindvertexbuffers = NULL;
typedef void (APIENTRY *PFNGLBITMAPPROC)(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap);
PFNGLBITMAPPROC _gl_loader_glbitmap = NULL;
typedef void (APIENTRY *PFNGLBLENDCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLBLENDCOLORPROC _gl_loader_glblendcolor = NULL;
typedef void (APIENTRY *PFNGLBLENDEQUATIONPROC)(GLenum mode);
PFNGLBLENDEQUATIONPROC _gl_loader_glblendequation = NULL;
typedef void (APIENTRY *PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum modeRGB, GLenum modeAlpha);
PFNGLBLENDEQUATIONSEPARATEPROC _gl_loader_glblendequationseparate = NULL;
typedef void (APIENTRY *PFNGLBLENDEQUATIONSEPARATEIPROC)(GLuint buf, GLenum modeRGB, GLenum modeAlpha);
PFNGLBLENDEQUATIONSEPARATEIPROC _gl_loader_glblendequationseparatei = NULL;
typedef void (APIENTRY *PFNGLBLENDEQUATIONIPROC)(GLuint buf, GLenum mode);
PFNGLBLENDEQUATIONIPROC _gl_loader_glblendequationi = NULL;
typedef void (APIENTRY *PFNGLBLENDFUNCPROC)(GLenum sfactor, GLenum dfactor);
PFNGLBLENDFUNCPROC _gl_loader_glblendfunc = NULL;
typedef void (APIENTRY *PFNGLBLENDFUNCSEPARATEPROC)(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
PFNGLBLENDFUNCSEPARATEPROC _gl_loader_glblendfuncseparate = NULL;
typedef void (APIENTRY *PFNGLBLENDFUNCSEPARATEIPROC)(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
PFNGLBLENDFUNCSEPARATEIPROC _gl_loader_glblendfuncseparatei = NULL;
typedef void (APIENTRY *PFNGLBLENDFUNCIPROC)(GLuint buf, GLenum src, GLenum dst);
PFNGLBLENDFUNCIPROC _gl_loader_glblendfunci = NULL;
typedef void (APIENTRY *PFNGLBLITFRAMEBUFFERPROC)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
PFNGLBLITFRAMEBUFFERPROC _gl_loader_glblitframebuffer = NULL;
typedef void (APIENTRY *PFNGLBLITNAMEDFRAMEBUFFERPROC)(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);
PFNGLBLITNAMEDFRAMEBUFFERPROC _gl_loader_glblitnamedframebuffer = NULL;
typedef void (APIENTRY *PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
PFNGLBUFFERDATAPROC _gl_loader_glbufferdata = NULL;
typedef void (APIENTRY *PFNGLBUFFERSTORAGEPROC)(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags);
PFNGLBUFFERSTORAGEPROC _gl_loader_glbufferstorage = NULL;
typedef void (APIENTRY *PFNGLBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
PFNGLBUFFERSUBDATAPROC _gl_loader_glbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLCALLLISTPROC)(GLuint list);
PFNGLCALLLISTPROC _gl_loader_glcalllist = NULL;
typedef void (APIENTRY *PFNGLCALLLISTSPROC)(GLsizei n, GLenum type, const void * lists);
PFNGLCALLLISTSPROC _gl_loader_glcalllists = NULL;
typedef GLenum (APIENTRY *PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum target);
PFNGLCHECKFRAMEBUFFERSTATUSPROC _gl_loader_glcheckframebufferstatus = NULL;
typedef GLenum (APIENTRY *PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)(GLuint framebuffer, GLenum target);
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC _gl_loader_glchecknamedframebufferstatus = NULL;
typedef void (APIENTRY *PFNGLCLAMPCOLORPROC)(GLenum target, GLenum clamp);
PFNGLCLAMPCOLORPROC _gl_loader_glclampcolor = NULL;
typedef void (APIENTRY *PFNGLCLEARPROC)(GLbitfield mask);
PFNGLCLEARPROC _gl_loader_glclear = NULL;
typedef void (APIENTRY *PFNGLCLEARACCUMPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARACCUMPROC _gl_loader_glclearaccum = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERDATAPROC)(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data);
PFNGLCLEARBUFFERDATAPROC _gl_loader_glclearbufferdata = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERSUBDATAPROC)(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
PFNGLCLEARBUFFERSUBDATAPROC _gl_loader_glclearbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERFIPROC)(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
PFNGLCLEARBUFFERFIPROC _gl_loader_glclearbufferfi = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERFVPROC)(GLenum buffer, GLint drawbuffer, const GLfloat * value);
PFNGLCLEARBUFFERFVPROC _gl_loader_glclearbufferfv = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERIVPROC)(GLenum buffer, GLint drawbuffer, const GLint * value);
PFNGLCLEARBUFFERIVPROC _gl_loader_glclearbufferiv = NULL;
typedef void (APIENTRY *PFNGLCLEARBUFFERUIVPROC)(GLenum buffer, GLint drawbuffer, const GLuint * value);
PFNGLCLEARBUFFERUIVPROC _gl_loader_glclearbufferuiv = NULL;
typedef void (APIENTRY *PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARCOLORPROC _gl_loader_glclearcolor = NULL;
typedef void (APIENTRY *PFNGLCLEARDEPTHPROC)(GLdouble depth);
PFNGLCLEARDEPTHPROC _gl_loader_glcleardepth = NULL;
typedef void (APIENTRY *PFNGLCLEARDEPTHFPROC)(GLfloat d);
PFNGLCLEARDEPTHFPROC _gl_loader_glcleardepthf = NULL;
typedef void (APIENTRY *PFNGLCLEARINDEXPROC)(GLfloat c);
PFNGLCLEARINDEXPROC _gl_loader_glclearindex = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDBUFFERDATAPROC)(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data);
PFNGLCLEARNAMEDBUFFERDATAPROC _gl_loader_glclearnamedbufferdata = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data);
PFNGLCLEARNAMEDBUFFERSUBDATAPROC _gl_loader_glclearnamedbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil);
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC _gl_loader_glclearnamedframebufferfi = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value);
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC _gl_loader_glclearnamedframebufferfv = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value);
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC _gl_loader_glclearnamedframebufferiv = NULL;
typedef void (APIENTRY *PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value);
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC _gl_loader_glclearnamedframebufferuiv = NULL;
typedef void (APIENTRY *PFNGLCLEARSTENCILPROC)(GLint s);
PFNGLCLEARSTENCILPROC _gl_loader_glclearstencil = NULL;
typedef void (APIENTRY *PFNGLCLEARTEXIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, const void * data);
PFNGLCLEARTEXIMAGEPROC _gl_loader_glclearteximage = NULL;
typedef void (APIENTRY *PFNGLCLEARTEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data);
PFNGLCLEARTEXSUBIMAGEPROC _gl_loader_glcleartexsubimage = NULL;
typedef void (APIENTRY *PFNGLCLIENTACTIVETEXTUREPROC)(GLenum texture);
PFNGLCLIENTACTIVETEXTUREPROC _gl_loader_glclientactivetexture = NULL;
typedef GLenum (APIENTRY *PFNGLCLIENTWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
PFNGLCLIENTWAITSYNCPROC _gl_loader_glclientwaitsync = NULL;
typedef void (APIENTRY *PFNGLCLIPCONTROLPROC)(GLenum origin, GLenum depth);
PFNGLCLIPCONTROLPROC _gl_loader_glclipcontrol = NULL;
typedef void (APIENTRY *PFNGLCLIPPLANEPROC)(GLenum plane, const GLdouble * equation);
PFNGLCLIPPLANEPROC _gl_loader_glclipplane = NULL;
typedef void (APIENTRY *PFNGLCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
PFNGLCOLOR3BPROC _gl_loader_glcolor3b = NULL;
typedef void (APIENTRY *PFNGLCOLOR3BVPROC)(const GLbyte * v);
PFNGLCOLOR3BVPROC _gl_loader_glcolor3bv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
PFNGLCOLOR3DPROC _gl_loader_glcolor3d = NULL;
typedef void (APIENTRY *PFNGLCOLOR3DVPROC)(const GLdouble * v);
PFNGLCOLOR3DVPROC _gl_loader_glcolor3dv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
PFNGLCOLOR3FPROC _gl_loader_glcolor3f = NULL;
typedef void (APIENTRY *PFNGLCOLOR3FVPROC)(const GLfloat * v);
PFNGLCOLOR3FVPROC _gl_loader_glcolor3fv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3IPROC)(GLint red, GLint green, GLint blue);
PFNGLCOLOR3IPROC _gl_loader_glcolor3i = NULL;
typedef void (APIENTRY *PFNGLCOLOR3IVPROC)(const GLint * v);
PFNGLCOLOR3IVPROC _gl_loader_glcolor3iv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
PFNGLCOLOR3SPROC _gl_loader_glcolor3s = NULL;
typedef void (APIENTRY *PFNGLCOLOR3SVPROC)(const GLshort * v);
PFNGLCOLOR3SVPROC _gl_loader_glcolor3sv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
PFNGLCOLOR3UBPROC _gl_loader_glcolor3ub = NULL;
typedef void (APIENTRY *PFNGLCOLOR3UBVPROC)(const GLubyte * v);
PFNGLCOLOR3UBVPROC _gl_loader_glcolor3ubv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
PFNGLCOLOR3UIPROC _gl_loader_glcolor3ui = NULL;
typedef void (APIENTRY *PFNGLCOLOR3UIVPROC)(const GLuint * v);
PFNGLCOLOR3UIVPROC _gl_loader_glcolor3uiv = NULL;
typedef void (APIENTRY *PFNGLCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
PFNGLCOLOR3USPROC _gl_loader_glcolor3us = NULL;
typedef void (APIENTRY *PFNGLCOLOR3USVPROC)(const GLushort * v);
PFNGLCOLOR3USVPROC _gl_loader_glcolor3usv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4BPROC)(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
PFNGLCOLOR4BPROC _gl_loader_glcolor4b = NULL;
typedef void (APIENTRY *PFNGLCOLOR4BVPROC)(const GLbyte * v);
PFNGLCOLOR4BVPROC _gl_loader_glcolor4bv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4DPROC)(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
PFNGLCOLOR4DPROC _gl_loader_glcolor4d = NULL;
typedef void (APIENTRY *PFNGLCOLOR4DVPROC)(const GLdouble * v);
PFNGLCOLOR4DVPROC _gl_loader_glcolor4dv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4FPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCOLOR4FPROC _gl_loader_glcolor4f = NULL;
typedef void (APIENTRY *PFNGLCOLOR4FVPROC)(const GLfloat * v);
PFNGLCOLOR4FVPROC _gl_loader_glcolor4fv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4IPROC)(GLint red, GLint green, GLint blue, GLint alpha);
PFNGLCOLOR4IPROC _gl_loader_glcolor4i = NULL;
typedef void (APIENTRY *PFNGLCOLOR4IVPROC)(const GLint * v);
PFNGLCOLOR4IVPROC _gl_loader_glcolor4iv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4SPROC)(GLshort red, GLshort green, GLshort blue, GLshort alpha);
PFNGLCOLOR4SPROC _gl_loader_glcolor4s = NULL;
typedef void (APIENTRY *PFNGLCOLOR4SVPROC)(const GLshort * v);
PFNGLCOLOR4SVPROC _gl_loader_glcolor4sv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4UBPROC)(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
PFNGLCOLOR4UBPROC _gl_loader_glcolor4ub = NULL;
typedef void (APIENTRY *PFNGLCOLOR4UBVPROC)(const GLubyte * v);
PFNGLCOLOR4UBVPROC _gl_loader_glcolor4ubv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4UIPROC)(GLuint red, GLuint green, GLuint blue, GLuint alpha);
PFNGLCOLOR4UIPROC _gl_loader_glcolor4ui = NULL;
typedef void (APIENTRY *PFNGLCOLOR4UIVPROC)(const GLuint * v);
PFNGLCOLOR4UIVPROC _gl_loader_glcolor4uiv = NULL;
typedef void (APIENTRY *PFNGLCOLOR4USPROC)(GLushort red, GLushort green, GLushort blue, GLushort alpha);
PFNGLCOLOR4USPROC _gl_loader_glcolor4us = NULL;
typedef void (APIENTRY *PFNGLCOLOR4USVPROC)(const GLushort * v);
PFNGLCOLOR4USVPROC _gl_loader_glcolor4usv = NULL;
typedef void (APIENTRY *PFNGLCOLORMASKPROC)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
PFNGLCOLORMASKPROC _gl_loader_glcolormask = NULL;
typedef void (APIENTRY *PFNGLCOLORMASKIPROC)(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
PFNGLCOLORMASKIPROC _gl_loader_glcolormaski = NULL;
typedef void (APIENTRY *PFNGLCOLORMATERIALPROC)(GLenum face, GLenum mode);
PFNGLCOLORMATERIALPROC _gl_loader_glcolormaterial = NULL;
typedef void (APIENTRY *PFNGLCOLORP3UIPROC)(GLenum type, GLuint color);
PFNGLCOLORP3UIPROC _gl_loader_glcolorp3ui = NULL;
typedef void (APIENTRY *PFNGLCOLORP3UIVPROC)(GLenum type, const GLuint * color);
PFNGLCOLORP3UIVPROC _gl_loader_glcolorp3uiv = NULL;
typedef void (APIENTRY *PFNGLCOLORP4UIPROC)(GLenum type, GLuint color);
PFNGLCOLORP4UIPROC _gl_loader_glcolorp4ui = NULL;
typedef void (APIENTRY *PFNGLCOLORP4UIVPROC)(GLenum type, const GLuint * color);
PFNGLCOLORP4UIVPROC _gl_loader_glcolorp4uiv = NULL;
typedef void (APIENTRY *PFNGLCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLCOLORPOINTERPROC _gl_loader_glcolorpointer = NULL;
typedef void (APIENTRY *PFNGLCOMPILESHADERPROC)(GLuint shader);
PFNGLCOMPILESHADERPROC _gl_loader_glcompileshader = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXIMAGE1DPROC _gl_loader_glcompressedteximage1d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXIMAGE2DPROC _gl_loader_glcompressedteximage2d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXIMAGE3DPROC _gl_loader_glcompressedteximage3d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC _gl_loader_glcompressedtexsubimage1d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC _gl_loader_glcompressedtexsubimage2d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC _gl_loader_glcompressedtexsubimage3d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC _gl_loader_glcompressedtexturesubimage1d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC _gl_loader_glcompressedtexturesubimage2d = NULL;
typedef void (APIENTRY *PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data);
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC _gl_loader_glcompressedtexturesubimage3d = NULL;
typedef void (APIENTRY *PFNGLCOPYBUFFERSUBDATAPROC)(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
PFNGLCOPYBUFFERSUBDATAPROC _gl_loader_glcopybuffersubdata = NULL;
typedef void (APIENTRY *PFNGLCOPYIMAGESUBDATAPROC)(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
PFNGLCOPYIMAGESUBDATAPROC _gl_loader_glcopyimagesubdata = NULL;
typedef void (APIENTRY *PFNGLCOPYNAMEDBUFFERSUBDATAPROC)(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size);
PFNGLCOPYNAMEDBUFFERSUBDATAPROC _gl_loader_glcopynamedbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLCOPYPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
PFNGLCOPYPIXELSPROC _gl_loader_glcopypixels = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXIMAGE1DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border);
PFNGLCOPYTEXIMAGE1DPROC _gl_loader_glcopyteximage1d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXIMAGE2DPROC)(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
PFNGLCOPYTEXIMAGE2DPROC _gl_loader_glcopyteximage2d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
PFNGLCOPYTEXSUBIMAGE1DPROC _gl_loader_glcopytexsubimage1d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXSUBIMAGE2DPROC _gl_loader_glcopytexsubimage2d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXSUBIMAGE3DPROC _gl_loader_glcopytexsubimage3d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
PFNGLCOPYTEXTURESUBIMAGE1DPROC _gl_loader_glcopytexturesubimage1d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXTURESUBIMAGE2DPROC _gl_loader_glcopytexturesubimage2d = NULL;
typedef void (APIENTRY *PFNGLCOPYTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLCOPYTEXTURESUBIMAGE3DPROC _gl_loader_glcopytexturesubimage3d = NULL;
typedef void (APIENTRY *PFNGLCREATEBUFFERSPROC)(GLsizei n, GLuint * buffers);
PFNGLCREATEBUFFERSPROC _gl_loader_glcreatebuffers = NULL;
typedef void (APIENTRY *PFNGLCREATEFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
PFNGLCREATEFRAMEBUFFERSPROC _gl_loader_glcreateframebuffers = NULL;
typedef GLuint (APIENTRY *PFNGLCREATEPROGRAMPROC)();
PFNGLCREATEPROGRAMPROC _gl_loader_glcreateprogram = NULL;
typedef void (APIENTRY *PFNGLCREATEPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
PFNGLCREATEPROGRAMPIPELINESPROC _gl_loader_glcreateprogrampipelines = NULL;
typedef void (APIENTRY *PFNGLCREATEQUERIESPROC)(GLenum target, GLsizei n, GLuint * ids);
PFNGLCREATEQUERIESPROC _gl_loader_glcreatequeries = NULL;
typedef void (APIENTRY *PFNGLCREATERENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
PFNGLCREATERENDERBUFFERSPROC _gl_loader_glcreaterenderbuffers = NULL;
typedef void (APIENTRY *PFNGLCREATESAMPLERSPROC)(GLsizei n, GLuint * samplers);
PFNGLCREATESAMPLERSPROC _gl_loader_glcreatesamplers = NULL;
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROC)(GLenum type);
PFNGLCREATESHADERPROC _gl_loader_glcreateshader = NULL;
typedef GLuint (APIENTRY *PFNGLCREATESHADERPROGRAMVPROC)(GLenum type, GLsizei count, const GLchar * const * strings);
PFNGLCREATESHADERPROGRAMVPROC _gl_loader_glcreateshaderprogramv = NULL;
typedef void (APIENTRY *PFNGLCREATETEXTURESPROC)(GLenum target, GLsizei n, GLuint * textures);
PFNGLCREATETEXTURESPROC _gl_loader_glcreatetextures = NULL;
typedef void (APIENTRY *PFNGLCREATETRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
PFNGLCREATETRANSFORMFEEDBACKSPROC _gl_loader_glcreatetransformfeedbacks = NULL;
typedef void (APIENTRY *PFNGLCREATEVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
PFNGLCREATEVERTEXARRAYSPROC _gl_loader_glcreatevertexarrays = NULL;
typedef void (APIENTRY *PFNGLCULLFACEPROC)(GLenum mode);
PFNGLCULLFACEPROC _gl_loader_glcullface = NULL;
typedef void (APIENTRY *PFNGLDEBUGMESSAGECALLBACKPROC)(GLDEBUGPROC callback, const void * userParam);
PFNGLDEBUGMESSAGECALLBACKPROC _gl_loader_gldebugmessagecallback = NULL;
typedef void (APIENTRY *PFNGLDEBUGMESSAGECONTROLPROC)(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled);
PFNGLDEBUGMESSAGECONTROLPROC _gl_loader_gldebugmessagecontrol = NULL;
typedef void (APIENTRY *PFNGLDEBUGMESSAGEINSERTPROC)(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf);
PFNGLDEBUGMESSAGEINSERTPROC _gl_loader_gldebugmessageinsert = NULL;
typedef void (APIENTRY *PFNGLDELETEBUFFERSPROC)(GLsizei n, const GLuint * buffers);
PFNGLDELETEBUFFERSPROC _gl_loader_gldeletebuffers = NULL;
typedef void (APIENTRY *PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei n, const GLuint * framebuffers);
PFNGLDELETEFRAMEBUFFERSPROC _gl_loader_gldeleteframebuffers = NULL;
typedef void (APIENTRY *PFNGLDELETELISTSPROC)(GLuint list, GLsizei range);
PFNGLDELETELISTSPROC _gl_loader_gldeletelists = NULL;
typedef void (APIENTRY *PFNGLDELETEPROGRAMPROC)(GLuint program);
PFNGLDELETEPROGRAMPROC _gl_loader_gldeleteprogram = NULL;
typedef void (APIENTRY *PFNGLDELETEPROGRAMPIPELINESPROC)(GLsizei n, const GLuint * pipelines);
PFNGLDELETEPROGRAMPIPELINESPROC _gl_loader_gldeleteprogrampipelines = NULL;
typedef void (APIENTRY *PFNGLDELETEQUERIESPROC)(GLsizei n, const GLuint * ids);
PFNGLDELETEQUERIESPROC _gl_loader_gldeletequeries = NULL;
typedef void (APIENTRY *PFNGLDELETERENDERBUFFERSPROC)(GLsizei n, const GLuint * renderbuffers);
PFNGLDELETERENDERBUFFERSPROC _gl_loader_gldeleterenderbuffers = NULL;
typedef void (APIENTRY *PFNGLDELETESAMPLERSPROC)(GLsizei count, const GLuint * samplers);
PFNGLDELETESAMPLERSPROC _gl_loader_gldeletesamplers = NULL;
typedef void (APIENTRY *PFNGLDELETESHADERPROC)(GLuint shader);
PFNGLDELETESHADERPROC _gl_loader_gldeleteshader = NULL;
typedef void (APIENTRY *PFNGLDELETESYNCPROC)(GLsync sync);
PFNGLDELETESYNCPROC _gl_loader_gldeletesync = NULL;
typedef void (APIENTRY *PFNGLDELETETEXTURESPROC)(GLsizei n, const GLuint * textures);
PFNGLDELETETEXTURESPROC _gl_loader_gldeletetextures = NULL;
typedef void (APIENTRY *PFNGLDELETETRANSFORMFEEDBACKSPROC)(GLsizei n, const GLuint * ids);
PFNGLDELETETRANSFORMFEEDBACKSPROC _gl_loader_gldeletetransformfeedbacks = NULL;
typedef void (APIENTRY *PFNGLDELETEVERTEXARRAYSPROC)(GLsizei n, const GLuint * arrays);
PFNGLDELETEVERTEXARRAYSPROC _gl_loader_gldeletevertexarrays = NULL;
typedef void (APIENTRY *PFNGLDEPTHFUNCPROC)(GLenum func);
PFNGLDEPTHFUNCPROC _gl_loader_gldepthfunc = NULL;
typedef void (APIENTRY *PFNGLDEPTHMASKPROC)(GLboolean flag);
PFNGLDEPTHMASKPROC _gl_loader_gldepthmask = NULL;
typedef void (APIENTRY *PFNGLDEPTHRANGEPROC)(GLdouble n, GLdouble f);
PFNGLDEPTHRANGEPROC _gl_loader_gldepthrange = NULL;
typedef void (APIENTRY *PFNGLDEPTHRANGEARRAYVPROC)(GLuint first, GLsizei count, const GLdouble * v);
PFNGLDEPTHRANGEARRAYVPROC _gl_loader_gldepthrangearrayv = NULL;
typedef void (APIENTRY *PFNGLDEPTHRANGEINDEXEDPROC)(GLuint index, GLdouble n, GLdouble f);
PFNGLDEPTHRANGEINDEXEDPROC _gl_loader_gldepthrangeindexed = NULL;
typedef void (APIENTRY *PFNGLDEPTHRANGEFPROC)(GLfloat n, GLfloat f);
PFNGLDEPTHRANGEFPROC _gl_loader_gldepthrangef = NULL;
typedef void (APIENTRY *PFNGLDETACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLDETACHSHADERPROC _gl_loader_gldetachshader = NULL;
typedef void (APIENTRY *PFNGLDISABLEPROC)(GLenum cap);
PFNGLDISABLEPROC _gl_loader_gldisable = NULL;
typedef void (APIENTRY *PFNGLDISABLECLIENTSTATEPROC)(GLenum array);
PFNGLDISABLECLIENTSTATEPROC _gl_loader_gldisableclientstate = NULL;
typedef void (APIENTRY *PFNGLDISABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
PFNGLDISABLEVERTEXARRAYATTRIBPROC _gl_loader_gldisablevertexarrayattrib = NULL;
typedef void (APIENTRY *PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLDISABLEVERTEXATTRIBARRAYPROC _gl_loader_gldisablevertexattribarray = NULL;
typedef void (APIENTRY *PFNGLDISABLEIPROC)(GLenum target, GLuint index);
PFNGLDISABLEIPROC _gl_loader_gldisablei = NULL;
typedef void (APIENTRY *PFNGLDISPATCHCOMPUTEPROC)(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z);
PFNGLDISPATCHCOMPUTEPROC _gl_loader_gldispatchcompute = NULL;
typedef void (APIENTRY *PFNGLDISPATCHCOMPUTEINDIRECTPROC)(GLintptr indirect);
PFNGLDISPATCHCOMPUTEINDIRECTPROC _gl_loader_gldispatchcomputeindirect = NULL;
typedef void (APIENTRY *PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
PFNGLDRAWARRAYSPROC _gl_loader_gldrawarrays = NULL;
typedef void (APIENTRY *PFNGLDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect);
PFNGLDRAWARRAYSINDIRECTPROC _gl_loader_gldrawarraysindirect = NULL;
typedef void (APIENTRY *PFNGLDRAWARRAYSINSTANCEDPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
PFNGLDRAWARRAYSINSTANCEDPROC _gl_loader_gldrawarraysinstanced = NULL;
typedef void (APIENTRY *PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance);
PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC _gl_loader_gldrawarraysinstancedbaseinstance = NULL;
typedef void (APIENTRY *PFNGLDRAWBUFFERPROC)(GLenum buf);
PFNGLDRAWBUFFERPROC _gl_loader_gldrawbuffer = NULL;
typedef void (APIENTRY *PFNGLDRAWBUFFERSPROC)(GLsizei n, const GLenum * bufs);
PFNGLDRAWBUFFERSPROC _gl_loader_gldrawbuffers = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices);
PFNGLDRAWELEMENTSPROC _gl_loader_gldrawelements = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex);
PFNGLDRAWELEMENTSBASEVERTEXPROC _gl_loader_gldrawelementsbasevertex = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect);
PFNGLDRAWELEMENTSINDIRECTPROC _gl_loader_gldrawelementsindirect = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSINSTANCEDPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount);
PFNGLDRAWELEMENTSINSTANCEDPROC _gl_loader_gldrawelementsinstanced = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance);
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC _gl_loader_gldrawelementsinstancedbaseinstance = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex);
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC _gl_loader_gldrawelementsinstancedbasevertex = NULL;
typedef void (APIENTRY *PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance);
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC _gl_loader_gldrawelementsinstancedbasevertexbaseinstance = NULL;
typedef void (APIENTRY *PFNGLDRAWPIXELSPROC)(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
PFNGLDRAWPIXELSPROC _gl_loader_gldrawpixels = NULL;
typedef void (APIENTRY *PFNGLDRAWRANGEELEMENTSPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices);
PFNGLDRAWRANGEELEMENTSPROC _gl_loader_gldrawrangeelements = NULL;
typedef void (APIENTRY *PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex);
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC _gl_loader_gldrawrangeelementsbasevertex = NULL;
typedef void (APIENTRY *PFNGLDRAWTRANSFORMFEEDBACKPROC)(GLenum mode, GLuint id);
PFNGLDRAWTRANSFORMFEEDBACKPROC _gl_loader_gldrawtransformfeedback = NULL;
typedef void (APIENTRY *PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)(GLenum mode, GLuint id, GLsizei instancecount);
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC _gl_loader_gldrawtransformfeedbackinstanced = NULL;
typedef void (APIENTRY *PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)(GLenum mode, GLuint id, GLuint stream);
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC _gl_loader_gldrawtransformfeedbackstream = NULL;
typedef void (APIENTRY *PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount);
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC _gl_loader_gldrawtransformfeedbackstreaminstanced = NULL;
typedef void (APIENTRY *PFNGLEDGEFLAGPROC)(GLboolean flag);
PFNGLEDGEFLAGPROC _gl_loader_gledgeflag = NULL;
typedef void (APIENTRY *PFNGLEDGEFLAGPOINTERPROC)(GLsizei stride, const void * pointer);
PFNGLEDGEFLAGPOINTERPROC _gl_loader_gledgeflagpointer = NULL;
typedef void (APIENTRY *PFNGLEDGEFLAGVPROC)(const GLboolean * flag);
PFNGLEDGEFLAGVPROC _gl_loader_gledgeflagv = NULL;
typedef void (APIENTRY *PFNGLENABLEPROC)(GLenum cap);
PFNGLENABLEPROC _gl_loader_glenable = NULL;
typedef void (APIENTRY *PFNGLENABLECLIENTSTATEPROC)(GLenum array);
PFNGLENABLECLIENTSTATEPROC _gl_loader_glenableclientstate = NULL;
typedef void (APIENTRY *PFNGLENABLEVERTEXARRAYATTRIBPROC)(GLuint vaobj, GLuint index);
PFNGLENABLEVERTEXARRAYATTRIBPROC _gl_loader_glenablevertexarrayattrib = NULL;
typedef void (APIENTRY *PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLENABLEVERTEXATTRIBARRAYPROC _gl_loader_glenablevertexattribarray = NULL;
typedef void (APIENTRY *PFNGLENABLEIPROC)(GLenum target, GLuint index);
PFNGLENABLEIPROC _gl_loader_glenablei = NULL;
typedef void (APIENTRY *PFNGLENDPROC)();
PFNGLENDPROC _gl_loader_glend = NULL;
typedef void (APIENTRY *PFNGLENDCONDITIONALRENDERPROC)();
PFNGLENDCONDITIONALRENDERPROC _gl_loader_glendconditionalrender = NULL;
typedef void (APIENTRY *PFNGLENDLISTPROC)();
PFNGLENDLISTPROC _gl_loader_glendlist = NULL;
typedef void (APIENTRY *PFNGLENDQUERYPROC)(GLenum target);
PFNGLENDQUERYPROC _gl_loader_glendquery = NULL;
typedef void (APIENTRY *PFNGLENDQUERYINDEXEDPROC)(GLenum target, GLuint index);
PFNGLENDQUERYINDEXEDPROC _gl_loader_glendqueryindexed = NULL;
typedef void (APIENTRY *PFNGLENDTRANSFORMFEEDBACKPROC)();
PFNGLENDTRANSFORMFEEDBACKPROC _gl_loader_glendtransformfeedback = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD1DPROC)(GLdouble u);
PFNGLEVALCOORD1DPROC _gl_loader_glevalcoord1d = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD1DVPROC)(const GLdouble * u);
PFNGLEVALCOORD1DVPROC _gl_loader_glevalcoord1dv = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD1FPROC)(GLfloat u);
PFNGLEVALCOORD1FPROC _gl_loader_glevalcoord1f = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD1FVPROC)(const GLfloat * u);
PFNGLEVALCOORD1FVPROC _gl_loader_glevalcoord1fv = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD2DPROC)(GLdouble u, GLdouble v);
PFNGLEVALCOORD2DPROC _gl_loader_glevalcoord2d = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD2DVPROC)(const GLdouble * u);
PFNGLEVALCOORD2DVPROC _gl_loader_glevalcoord2dv = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD2FPROC)(GLfloat u, GLfloat v);
PFNGLEVALCOORD2FPROC _gl_loader_glevalcoord2f = NULL;
typedef void (APIENTRY *PFNGLEVALCOORD2FVPROC)(const GLfloat * u);
PFNGLEVALCOORD2FVPROC _gl_loader_glevalcoord2fv = NULL;
typedef void (APIENTRY *PFNGLEVALMESH1PROC)(GLenum mode, GLint i1, GLint i2);
PFNGLEVALMESH1PROC _gl_loader_glevalmesh1 = NULL;
typedef void (APIENTRY *PFNGLEVALMESH2PROC)(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
PFNGLEVALMESH2PROC _gl_loader_glevalmesh2 = NULL;
typedef void (APIENTRY *PFNGLEVALPOINT1PROC)(GLint i);
PFNGLEVALPOINT1PROC _gl_loader_glevalpoint1 = NULL;
typedef void (APIENTRY *PFNGLEVALPOINT2PROC)(GLint i, GLint j);
PFNGLEVALPOINT2PROC _gl_loader_glevalpoint2 = NULL;
typedef void (APIENTRY *PFNGLFEEDBACKBUFFERPROC)(GLsizei size, GLenum type, GLfloat * buffer);
PFNGLFEEDBACKBUFFERPROC _gl_loader_glfeedbackbuffer = NULL;
typedef GLsync (APIENTRY *PFNGLFENCESYNCPROC)(GLenum condition, GLbitfield flags);
PFNGLFENCESYNCPROC _gl_loader_glfencesync = NULL;
typedef void (APIENTRY *PFNGLFINISHPROC)();
PFNGLFINISHPROC _gl_loader_glfinish = NULL;
typedef void (APIENTRY *PFNGLFLUSHPROC)();
PFNGLFLUSHPROC _gl_loader_glflush = NULL;
typedef void (APIENTRY *PFNGLFLUSHMAPPEDBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length);
PFNGLFLUSHMAPPEDBUFFERRANGEPROC _gl_loader_glflushmappedbufferrange = NULL;
typedef void (APIENTRY *PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC _gl_loader_glflushmappednamedbufferrange = NULL;
typedef void (APIENTRY *PFNGLFOGCOORDPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
PFNGLFOGCOORDPOINTERPROC _gl_loader_glfogcoordpointer = NULL;
typedef void (APIENTRY *PFNGLFOGCOORDDPROC)(GLdouble coord);
PFNGLFOGCOORDDPROC _gl_loader_glfogcoordd = NULL;
typedef void (APIENTRY *PFNGLFOGCOORDDVPROC)(const GLdouble * coord);
PFNGLFOGCOORDDVPROC _gl_loader_glfogcoorddv = NULL;
typedef void (APIENTRY *PFNGLFOGCOORDFPROC)(GLfloat coord);
PFNGLFOGCOORDFPROC _gl_loader_glfogcoordf = NULL;
typedef void (APIENTRY *PFNGLFOGCOORDFVPROC)(const GLfloat * coord);
PFNGLFOGCOORDFVPROC _gl_loader_glfogcoordfv = NULL;
typedef void (APIENTRY *PFNGLFOGFPROC)(GLenum pname, GLfloat param);
PFNGLFOGFPROC _gl_loader_glfogf = NULL;
typedef void (APIENTRY *PFNGLFOGFVPROC)(GLenum pname, const GLfloat * params);
PFNGLFOGFVPROC _gl_loader_glfogfv = NULL;
typedef void (APIENTRY *PFNGLFOGIPROC)(GLenum pname, GLint param);
PFNGLFOGIPROC _gl_loader_glfogi = NULL;
typedef void (APIENTRY *PFNGLFOGIVPROC)(GLenum pname, const GLint * params);
PFNGLFOGIVPROC _gl_loader_glfogiv = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
PFNGLFRAMEBUFFERPARAMETERIPROC _gl_loader_glframebufferparameteri = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
PFNGLFRAMEBUFFERRENDERBUFFERPROC _gl_loader_glframebufferrenderbuffer = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERTEXTUREPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level);
PFNGLFRAMEBUFFERTEXTUREPROC _gl_loader_glframebuffertexture = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
PFNGLFRAMEBUFFERTEXTURE1DPROC _gl_loader_glframebuffertexture1d = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
PFNGLFRAMEBUFFERTEXTURE2DPROC _gl_loader_glframebuffertexture2d = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset);
PFNGLFRAMEBUFFERTEXTURE3DPROC _gl_loader_glframebuffertexture3d = NULL;
typedef void (APIENTRY *PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer);
PFNGLFRAMEBUFFERTEXTURELAYERPROC _gl_loader_glframebuffertexturelayer = NULL;
typedef void (APIENTRY *PFNGLFRONTFACEPROC)(GLenum mode);
PFNGLFRONTFACEPROC _gl_loader_glfrontface = NULL;
typedef void (APIENTRY *PFNGLFRUSTUMPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
PFNGLFRUSTUMPROC _gl_loader_glfrustum = NULL;
typedef void (APIENTRY *PFNGLGENBUFFERSPROC)(GLsizei n, GLuint * buffers);
PFNGLGENBUFFERSPROC _gl_loader_glgenbuffers = NULL;
typedef void (APIENTRY *PFNGLGENFRAMEBUFFERSPROC)(GLsizei n, GLuint * framebuffers);
PFNGLGENFRAMEBUFFERSPROC _gl_loader_glgenframebuffers = NULL;
typedef GLuint (APIENTRY *PFNGLGENLISTSPROC)(GLsizei range);
PFNGLGENLISTSPROC _gl_loader_glgenlists = NULL;
typedef void (APIENTRY *PFNGLGENPROGRAMPIPELINESPROC)(GLsizei n, GLuint * pipelines);
PFNGLGENPROGRAMPIPELINESPROC _gl_loader_glgenprogrampipelines = NULL;
typedef void (APIENTRY *PFNGLGENQUERIESPROC)(GLsizei n, GLuint * ids);
PFNGLGENQUERIESPROC _gl_loader_glgenqueries = NULL;
typedef void (APIENTRY *PFNGLGENRENDERBUFFERSPROC)(GLsizei n, GLuint * renderbuffers);
PFNGLGENRENDERBUFFERSPROC _gl_loader_glgenrenderbuffers = NULL;
typedef void (APIENTRY *PFNGLGENSAMPLERSPROC)(GLsizei count, GLuint * samplers);
PFNGLGENSAMPLERSPROC _gl_loader_glgensamplers = NULL;
typedef void (APIENTRY *PFNGLGENTEXTURESPROC)(GLsizei n, GLuint * textures);
PFNGLGENTEXTURESPROC _gl_loader_glgentextures = NULL;
typedef void (APIENTRY *PFNGLGENTRANSFORMFEEDBACKSPROC)(GLsizei n, GLuint * ids);
PFNGLGENTRANSFORMFEEDBACKSPROC _gl_loader_glgentransformfeedbacks = NULL;
typedef void (APIENTRY *PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint * arrays);
PFNGLGENVERTEXARRAYSPROC _gl_loader_glgenvertexarrays = NULL;
typedef void (APIENTRY *PFNGLGENERATEMIPMAPPROC)(GLenum target);
PFNGLGENERATEMIPMAPPROC _gl_loader_glgeneratemipmap = NULL;
typedef void (APIENTRY *PFNGLGENERATETEXTUREMIPMAPPROC)(GLuint texture);
PFNGLGENERATETEXTUREMIPMAPPROC _gl_loader_glgeneratetexturemipmap = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params);
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC _gl_loader_glgetactiveatomiccounterbufferiv = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEATTRIBPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
PFNGLGETACTIVEATTRIBPROC _gl_loader_glgetactiveattrib = NULL;
typedef void (APIENTRY *PFNGLGETACTIVESUBROUTINENAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
PFNGLGETACTIVESUBROUTINENAMEPROC _gl_loader_glgetactivesubroutinename = NULL;
typedef void (APIENTRY *PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC _gl_loader_glgetactivesubroutineuniformname = NULL;
typedef void (APIENTRY *PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values);
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC _gl_loader_glgetactivesubroutineuniformiv = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEUNIFORMPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
PFNGLGETACTIVEUNIFORMPROC _gl_loader_glgetactiveuniform = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName);
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC _gl_loader_glgetactiveuniformblockname = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEUNIFORMBLOCKIVPROC)(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params);
PFNGLGETACTIVEUNIFORMBLOCKIVPROC _gl_loader_glgetactiveuniformblockiv = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEUNIFORMNAMEPROC)(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName);
PFNGLGETACTIVEUNIFORMNAMEPROC _gl_loader_glgetactiveuniformname = NULL;
typedef void (APIENTRY *PFNGLGETACTIVEUNIFORMSIVPROC)(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params);
PFNGLGETACTIVEUNIFORMSIVPROC _gl_loader_glgetactiveuniformsiv = NULL;
typedef void (APIENTRY *PFNGLGETATTACHEDSHADERSPROC)(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
PFNGLGETATTACHEDSHADERSPROC _gl_loader_glgetattachedshaders = NULL;
typedef GLint (APIENTRY *PFNGLGETATTRIBLOCATIONPROC)(GLuint program, const GLchar * name);
PFNGLGETATTRIBLOCATIONPROC _gl_loader_glgetattriblocation = NULL;
typedef void (APIENTRY *PFNGLGETBOOLEANI_VPROC)(GLenum target, GLuint index, GLboolean * data);
PFNGLGETBOOLEANI_VPROC _gl_loader_glgetbooleani_v = NULL;
typedef void (APIENTRY *PFNGLGETBOOLEANVPROC)(GLenum pname, GLboolean * data);
PFNGLGETBOOLEANVPROC _gl_loader_glgetbooleanv = NULL;
typedef void (APIENTRY *PFNGLGETBUFFERPARAMETERI64VPROC)(GLenum target, GLenum pname, GLint64 * params);
PFNGLGETBUFFERPARAMETERI64VPROC _gl_loader_glgetbufferparameteri64v = NULL;
typedef void (APIENTRY *PFNGLGETBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETBUFFERPARAMETERIVPROC _gl_loader_glgetbufferparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETBUFFERPOINTERVPROC)(GLenum target, GLenum pname, void * * params);
PFNGLGETBUFFERPOINTERVPROC _gl_loader_glgetbufferpointerv = NULL;
typedef void (APIENTRY *PFNGLGETBUFFERSUBDATAPROC)(GLenum target, GLintptr offset, GLsizeiptr size, void * data);
PFNGLGETBUFFERSUBDATAPROC _gl_loader_glgetbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLGETCLIPPLANEPROC)(GLenum plane, GLdouble * equation);
PFNGLGETCLIPPLANEPROC _gl_loader_glgetclipplane = NULL;
typedef void (APIENTRY *PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint level, void * img);
PFNGLGETCOMPRESSEDTEXIMAGEPROC _gl_loader_glgetcompressedteximage = NULL;
typedef void (APIENTRY *PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLsizei bufSize, void * pixels);
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC _gl_loader_glgetcompressedtextureimage = NULL;
typedef void (APIENTRY *PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels);
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC _gl_loader_glgetcompressedtexturesubimage = NULL;
typedef GLuint (APIENTRY *PFNGLGETDEBUGMESSAGELOGPROC)(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog);
PFNGLGETDEBUGMESSAGELOGPROC _gl_loader_glgetdebugmessagelog = NULL;
typedef void (APIENTRY *PFNGLGETDOUBLEI_VPROC)(GLenum target, GLuint index, GLdouble * data);
PFNGLGETDOUBLEI_VPROC _gl_loader_glgetdoublei_v = NULL;
typedef void (APIENTRY *PFNGLGETDOUBLEVPROC)(GLenum pname, GLdouble * data);
PFNGLGETDOUBLEVPROC _gl_loader_glgetdoublev = NULL;
typedef GLenum (APIENTRY *PFNGLGETERRORPROC)();
PFNGLGETERRORPROC _gl_loader_glgeterror = NULL;
typedef void (APIENTRY *PFNGLGETFLOATI_VPROC)(GLenum target, GLuint index, GLfloat * data);
PFNGLGETFLOATI_VPROC _gl_loader_glgetfloati_v = NULL;
typedef void (APIENTRY *PFNGLGETFLOATVPROC)(GLenum pname, GLfloat * data);
PFNGLGETFLOATVPROC _gl_loader_glgetfloatv = NULL;
typedef GLint (APIENTRY *PFNGLGETFRAGDATAINDEXPROC)(GLuint program, const GLchar * name);
PFNGLGETFRAGDATAINDEXPROC _gl_loader_glgetfragdataindex = NULL;
typedef GLint (APIENTRY *PFNGLGETFRAGDATALOCATIONPROC)(GLuint program, const GLchar * name);
PFNGLGETFRAGDATALOCATIONPROC _gl_loader_glgetfragdatalocation = NULL;
typedef void (APIENTRY *PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum target, GLenum attachment, GLenum pname, GLint * params);
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC _gl_loader_glgetframebufferattachmentparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETFRAMEBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETFRAMEBUFFERPARAMETERIVPROC _gl_loader_glgetframebufferparameteriv = NULL;
typedef GLenum (APIENTRY *PFNGLGETGRAPHICSRESETSTATUSPROC)();
PFNGLGETGRAPHICSRESETSTATUSPROC _gl_loader_glgetgraphicsresetstatus = NULL;
typedef void (APIENTRY *PFNGLGETINTEGER64I_VPROC)(GLenum target, GLuint index, GLint64 * data);
PFNGLGETINTEGER64I_VPROC _gl_loader_glgetinteger64i_v = NULL;
typedef void (APIENTRY *PFNGLGETINTEGER64VPROC)(GLenum pname, GLint64 * data);
PFNGLGETINTEGER64VPROC _gl_loader_glgetinteger64v = NULL;
typedef void (APIENTRY *PFNGLGETINTEGERI_VPROC)(GLenum target, GLuint index, GLint * data);
PFNGLGETINTEGERI_VPROC _gl_loader_glgetintegeri_v = NULL;
typedef void (APIENTRY *PFNGLGETINTEGERVPROC)(GLenum pname, GLint * data);
PFNGLGETINTEGERVPROC _gl_loader_glgetintegerv = NULL;
typedef void (APIENTRY *PFNGLGETINTERNALFORMATI64VPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 * params);
PFNGLGETINTERNALFORMATI64VPROC _gl_loader_glgetinternalformati64v = NULL;
typedef void (APIENTRY *PFNGLGETINTERNALFORMATIVPROC)(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint * params);
PFNGLGETINTERNALFORMATIVPROC _gl_loader_glgetinternalformativ = NULL;
typedef void (APIENTRY *PFNGLGETLIGHTFVPROC)(GLenum light, GLenum pname, GLfloat * params);
PFNGLGETLIGHTFVPROC _gl_loader_glgetlightfv = NULL;
typedef void (APIENTRY *PFNGLGETLIGHTIVPROC)(GLenum light, GLenum pname, GLint * params);
PFNGLGETLIGHTIVPROC _gl_loader_glgetlightiv = NULL;
typedef void (APIENTRY *PFNGLGETMAPDVPROC)(GLenum target, GLenum query, GLdouble * v);
PFNGLGETMAPDVPROC _gl_loader_glgetmapdv = NULL;
typedef void (APIENTRY *PFNGLGETMAPFVPROC)(GLenum target, GLenum query, GLfloat * v);
PFNGLGETMAPFVPROC _gl_loader_glgetmapfv = NULL;
typedef void (APIENTRY *PFNGLGETMAPIVPROC)(GLenum target, GLenum query, GLint * v);
PFNGLGETMAPIVPROC _gl_loader_glgetmapiv = NULL;
typedef void (APIENTRY *PFNGLGETMATERIALFVPROC)(GLenum face, GLenum pname, GLfloat * params);
PFNGLGETMATERIALFVPROC _gl_loader_glgetmaterialfv = NULL;
typedef void (APIENTRY *PFNGLGETMATERIALIVPROC)(GLenum face, GLenum pname, GLint * params);
PFNGLGETMATERIALIVPROC _gl_loader_glgetmaterialiv = NULL;
typedef void (APIENTRY *PFNGLGETMULTISAMPLEFVPROC)(GLenum pname, GLuint index, GLfloat * val);
PFNGLGETMULTISAMPLEFVPROC _gl_loader_glgetmultisamplefv = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)(GLuint buffer, GLenum pname, GLint64 * params);
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC _gl_loader_glgetnamedbufferparameteri64v = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDBUFFERPARAMETERIVPROC)(GLuint buffer, GLenum pname, GLint * params);
PFNGLGETNAMEDBUFFERPARAMETERIVPROC _gl_loader_glgetnamedbufferparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDBUFFERPOINTERVPROC)(GLuint buffer, GLenum pname, void * * params);
PFNGLGETNAMEDBUFFERPOINTERVPROC _gl_loader_glgetnamedbufferpointerv = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data);
PFNGLGETNAMEDBUFFERSUBDATAPROC _gl_loader_glgetnamedbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params);
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC _gl_loader_glgetnamedframebufferattachmentparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)(GLuint framebuffer, GLenum pname, GLint * param);
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC _gl_loader_glgetnamedframebufferparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)(GLuint renderbuffer, GLenum pname, GLint * params);
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC _gl_loader_glgetnamedrenderbufferparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label);
PFNGLGETOBJECTLABELPROC _gl_loader_glgetobjectlabel = NULL;
typedef void (APIENTRY *PFNGLGETOBJECTPTRLABELPROC)(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label);
PFNGLGETOBJECTPTRLABELPROC _gl_loader_glgetobjectptrlabel = NULL;
typedef void (APIENTRY *PFNGLGETPIXELMAPFVPROC)(GLenum map, GLfloat * values);
PFNGLGETPIXELMAPFVPROC _gl_loader_glgetpixelmapfv = NULL;
typedef void (APIENTRY *PFNGLGETPIXELMAPUIVPROC)(GLenum map, GLuint * values);
PFNGLGETPIXELMAPUIVPROC _gl_loader_glgetpixelmapuiv = NULL;
typedef void (APIENTRY *PFNGLGETPIXELMAPUSVPROC)(GLenum map, GLushort * values);
PFNGLGETPIXELMAPUSVPROC _gl_loader_glgetpixelmapusv = NULL;
typedef void (APIENTRY *PFNGLGETPOINTERVPROC)(GLenum pname, void * * params);
PFNGLGETPOINTERVPROC _gl_loader_glgetpointerv = NULL;
typedef void (APIENTRY *PFNGLGETPOLYGONSTIPPLEPROC)(GLubyte * mask);
PFNGLGETPOLYGONSTIPPLEPROC _gl_loader_glgetpolygonstipple = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMBINARYPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary);
PFNGLGETPROGRAMBINARYPROC _gl_loader_glgetprogrambinary = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
PFNGLGETPROGRAMINFOLOGPROC _gl_loader_glgetprograminfolog = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMINTERFACEIVPROC)(GLuint program, GLenum programInterface, GLenum pname, GLint * params);
PFNGLGETPROGRAMINTERFACEIVPROC _gl_loader_glgetprograminterfaceiv = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMPIPELINEINFOLOGPROC)(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
PFNGLGETPROGRAMPIPELINEINFOLOGPROC _gl_loader_glgetprogrampipelineinfolog = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMPIPELINEIVPROC)(GLuint pipeline, GLenum pname, GLint * params);
PFNGLGETPROGRAMPIPELINEIVPROC _gl_loader_glgetprogrampipelineiv = NULL;
typedef GLuint (APIENTRY *PFNGLGETPROGRAMRESOURCEINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
PFNGLGETPROGRAMRESOURCEINDEXPROC _gl_loader_glgetprogramresourceindex = NULL;
typedef GLint (APIENTRY *PFNGLGETPROGRAMRESOURCELOCATIONPROC)(GLuint program, GLenum programInterface, const GLchar * name);
PFNGLGETPROGRAMRESOURCELOCATIONPROC _gl_loader_glgetprogramresourcelocation = NULL;
typedef GLint (APIENTRY *PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)(GLuint program, GLenum programInterface, const GLchar * name);
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC _gl_loader_glgetprogramresourcelocationindex = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMRESOURCENAMEPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name);
PFNGLGETPROGRAMRESOURCENAMEPROC _gl_loader_glgetprogramresourcename = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMRESOURCEIVPROC)(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei count, GLsizei * length, GLint * params);
PFNGLGETPROGRAMRESOURCEIVPROC _gl_loader_glgetprogramresourceiv = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMSTAGEIVPROC)(GLuint program, GLenum shadertype, GLenum pname, GLint * values);
PFNGLGETPROGRAMSTAGEIVPROC _gl_loader_glgetprogramstageiv = NULL;
typedef void (APIENTRY *PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint * params);
PFNGLGETPROGRAMIVPROC _gl_loader_glgetprogramiv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYBUFFEROBJECTI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
PFNGLGETQUERYBUFFEROBJECTI64VPROC _gl_loader_glgetquerybufferobjecti64v = NULL;
typedef void (APIENTRY *PFNGLGETQUERYBUFFEROBJECTIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
PFNGLGETQUERYBUFFEROBJECTIVPROC _gl_loader_glgetquerybufferobjectiv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYBUFFEROBJECTUI64VPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
PFNGLGETQUERYBUFFEROBJECTUI64VPROC _gl_loader_glgetquerybufferobjectui64v = NULL;
typedef void (APIENTRY *PFNGLGETQUERYBUFFEROBJECTUIVPROC)(GLuint id, GLuint buffer, GLenum pname, GLintptr offset);
PFNGLGETQUERYBUFFEROBJECTUIVPROC _gl_loader_glgetquerybufferobjectuiv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYINDEXEDIVPROC)(GLenum target, GLuint index, GLenum pname, GLint * params);
PFNGLGETQUERYINDEXEDIVPROC _gl_loader_glgetqueryindexediv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYOBJECTI64VPROC)(GLuint id, GLenum pname, GLint64 * params);
PFNGLGETQUERYOBJECTI64VPROC _gl_loader_glgetqueryobjecti64v = NULL;
typedef void (APIENTRY *PFNGLGETQUERYOBJECTIVPROC)(GLuint id, GLenum pname, GLint * params);
PFNGLGETQUERYOBJECTIVPROC _gl_loader_glgetqueryobjectiv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYOBJECTUI64VPROC)(GLuint id, GLenum pname, GLuint64 * params);
PFNGLGETQUERYOBJECTUI64VPROC _gl_loader_glgetqueryobjectui64v = NULL;
typedef void (APIENTRY *PFNGLGETQUERYOBJECTUIVPROC)(GLuint id, GLenum pname, GLuint * params);
PFNGLGETQUERYOBJECTUIVPROC _gl_loader_glgetqueryobjectuiv = NULL;
typedef void (APIENTRY *PFNGLGETQUERYIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETQUERYIVPROC _gl_loader_glgetqueryiv = NULL;
typedef void (APIENTRY *PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETRENDERBUFFERPARAMETERIVPROC _gl_loader_glgetrenderbufferparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, GLint * params);
PFNGLGETSAMPLERPARAMETERIIVPROC _gl_loader_glgetsamplerparameteriiv = NULL;
typedef void (APIENTRY *PFNGLGETSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, GLuint * params);
PFNGLGETSAMPLERPARAMETERIUIVPROC _gl_loader_glgetsamplerparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLGETSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, GLfloat * params);
PFNGLGETSAMPLERPARAMETERFVPROC _gl_loader_glgetsamplerparameterfv = NULL;
typedef void (APIENTRY *PFNGLGETSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, GLint * params);
PFNGLGETSAMPLERPARAMETERIVPROC _gl_loader_glgetsamplerparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
PFNGLGETSHADERINFOLOGPROC _gl_loader_glgetshaderinfolog = NULL;
typedef void (APIENTRY *PFNGLGETSHADERPRECISIONFORMATPROC)(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
PFNGLGETSHADERPRECISIONFORMATPROC _gl_loader_glgetshaderprecisionformat = NULL;
typedef void (APIENTRY *PFNGLGETSHADERSOURCEPROC)(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
PFNGLGETSHADERSOURCEPROC _gl_loader_glgetshadersource = NULL;
typedef void (APIENTRY *PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint * params);
PFNGLGETSHADERIVPROC _gl_loader_glgetshaderiv = NULL;
typedef GLubyte (APIENTRY *PFNGLGETSTRINGPROC)(GLenum name);
PFNGLGETSTRINGPROC _gl_loader_glgetstring = NULL;
typedef GLubyte (APIENTRY *PFNGLGETSTRINGIPROC)(GLenum name, GLuint index);
PFNGLGETSTRINGIPROC _gl_loader_glgetstringi = NULL;
typedef GLuint (APIENTRY *PFNGLGETSUBROUTINEINDEXPROC)(GLuint program, GLenum shadertype, const GLchar * name);
PFNGLGETSUBROUTINEINDEXPROC _gl_loader_glgetsubroutineindex = NULL;
typedef GLint (APIENTRY *PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)(GLuint program, GLenum shadertype, const GLchar * name);
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC _gl_loader_glgetsubroutineuniformlocation = NULL;
typedef void (APIENTRY *PFNGLGETSYNCIVPROC)(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values);
PFNGLGETSYNCIVPROC _gl_loader_glgetsynciv = NULL;
typedef void (APIENTRY *PFNGLGETTEXENVFVPROC)(GLenum target, GLenum pname, GLfloat * params);
PFNGLGETTEXENVFVPROC _gl_loader_glgettexenvfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXENVIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETTEXENVIVPROC _gl_loader_glgettexenviv = NULL;
typedef void (APIENTRY *PFNGLGETTEXGENDVPROC)(GLenum coord, GLenum pname, GLdouble * params);
PFNGLGETTEXGENDVPROC _gl_loader_glgettexgendv = NULL;
typedef void (APIENTRY *PFNGLGETTEXGENFVPROC)(GLenum coord, GLenum pname, GLfloat * params);
PFNGLGETTEXGENFVPROC _gl_loader_glgettexgenfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXGENIVPROC)(GLenum coord, GLenum pname, GLint * params);
PFNGLGETTEXGENIVPROC _gl_loader_glgettexgeniv = NULL;
typedef void (APIENTRY *PFNGLGETTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, void * pixels);
PFNGLGETTEXIMAGEPROC _gl_loader_glgetteximage = NULL;
typedef void (APIENTRY *PFNGLGETTEXLEVELPARAMETERFVPROC)(GLenum target, GLint level, GLenum pname, GLfloat * params);
PFNGLGETTEXLEVELPARAMETERFVPROC _gl_loader_glgettexlevelparameterfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXLEVELPARAMETERIVPROC)(GLenum target, GLint level, GLenum pname, GLint * params);
PFNGLGETTEXLEVELPARAMETERIVPROC _gl_loader_glgettexlevelparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETTEXPARAMETERIIVPROC _gl_loader_glgettexparameteriiv = NULL;
typedef void (APIENTRY *PFNGLGETTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, GLuint * params);
PFNGLGETTEXPARAMETERIUIVPROC _gl_loader_glgettexparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLGETTEXPARAMETERFVPROC)(GLenum target, GLenum pname, GLfloat * params);
PFNGLGETTEXPARAMETERFVPROC _gl_loader_glgettexparameterfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXPARAMETERIVPROC)(GLenum target, GLenum pname, GLint * params);
PFNGLGETTEXPARAMETERIVPROC _gl_loader_glgettexparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTUREIMAGEPROC)(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
PFNGLGETTEXTUREIMAGEPROC _gl_loader_glgettextureimage = NULL;
typedef void (APIENTRY *PFNGLGETTEXTURELEVELPARAMETERFVPROC)(GLuint texture, GLint level, GLenum pname, GLfloat * params);
PFNGLGETTEXTURELEVELPARAMETERFVPROC _gl_loader_glgettexturelevelparameterfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTURELEVELPARAMETERIVPROC)(GLuint texture, GLint level, GLenum pname, GLint * params);
PFNGLGETTEXTURELEVELPARAMETERIVPROC _gl_loader_glgettexturelevelparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, GLint * params);
PFNGLGETTEXTUREPARAMETERIIVPROC _gl_loader_glgettextureparameteriiv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, GLuint * params);
PFNGLGETTEXTUREPARAMETERIUIVPROC _gl_loader_glgettextureparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, GLfloat * params);
PFNGLGETTEXTUREPARAMETERFVPROC _gl_loader_glgettextureparameterfv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, GLint * params);
PFNGLGETTEXTUREPARAMETERIVPROC _gl_loader_glgettextureparameteriv = NULL;
typedef void (APIENTRY *PFNGLGETTEXTURESUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
PFNGLGETTEXTURESUBIMAGEPROC _gl_loader_glgettexturesubimage = NULL;
typedef void (APIENTRY *PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name);
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC _gl_loader_glgettransformfeedbackvarying = NULL;
typedef void (APIENTRY *PFNGLGETTRANSFORMFEEDBACKI64_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint64 * param);
PFNGLGETTRANSFORMFEEDBACKI64_VPROC _gl_loader_glgettransformfeedbacki64_v = NULL;
typedef void (APIENTRY *PFNGLGETTRANSFORMFEEDBACKI_VPROC)(GLuint xfb, GLenum pname, GLuint index, GLint * param);
PFNGLGETTRANSFORMFEEDBACKI_VPROC _gl_loader_glgettransformfeedbacki_v = NULL;
typedef void (APIENTRY *PFNGLGETTRANSFORMFEEDBACKIVPROC)(GLuint xfb, GLenum pname, GLint * param);
PFNGLGETTRANSFORMFEEDBACKIVPROC _gl_loader_glgettransformfeedbackiv = NULL;
typedef GLuint (APIENTRY *PFNGLGETUNIFORMBLOCKINDEXPROC)(GLuint program, const GLchar * uniformBlockName);
PFNGLGETUNIFORMBLOCKINDEXPROC _gl_loader_glgetuniformblockindex = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMINDICESPROC)(GLuint program, GLsizei uniformCount, const GLchar * const * uniformNames, GLuint * uniformIndices);
PFNGLGETUNIFORMINDICESPROC _gl_loader_glgetuniformindices = NULL;
typedef GLint (APIENTRY *PFNGLGETUNIFORMLOCATIONPROC)(GLuint program, const GLchar * name);
PFNGLGETUNIFORMLOCATIONPROC _gl_loader_glgetuniformlocation = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMSUBROUTINEUIVPROC)(GLenum shadertype, GLint location, GLuint * params);
PFNGLGETUNIFORMSUBROUTINEUIVPROC _gl_loader_glgetuniformsubroutineuiv = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMDVPROC)(GLuint program, GLint location, GLdouble * params);
PFNGLGETUNIFORMDVPROC _gl_loader_glgetuniformdv = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMFVPROC)(GLuint program, GLint location, GLfloat * params);
PFNGLGETUNIFORMFVPROC _gl_loader_glgetuniformfv = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMIVPROC)(GLuint program, GLint location, GLint * params);
PFNGLGETUNIFORMIVPROC _gl_loader_glgetuniformiv = NULL;
typedef void (APIENTRY *PFNGLGETUNIFORMUIVPROC)(GLuint program, GLint location, GLuint * params);
PFNGLGETUNIFORMUIVPROC _gl_loader_glgetuniformuiv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXARRAYINDEXED64IVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param);
PFNGLGETVERTEXARRAYINDEXED64IVPROC _gl_loader_glgetvertexarrayindexed64iv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXARRAYINDEXEDIVPROC)(GLuint vaobj, GLuint index, GLenum pname, GLint * param);
PFNGLGETVERTEXARRAYINDEXEDIVPROC _gl_loader_glgetvertexarrayindexediv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXARRAYIVPROC)(GLuint vaobj, GLenum pname, GLint * param);
PFNGLGETVERTEXARRAYIVPROC _gl_loader_glgetvertexarrayiv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBIIVPROC)(GLuint index, GLenum pname, GLint * params);
PFNGLGETVERTEXATTRIBIIVPROC _gl_loader_glgetvertexattribiiv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint index, GLenum pname, GLuint * params);
PFNGLGETVERTEXATTRIBIUIVPROC _gl_loader_glgetvertexattribiuiv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBLDVPROC)(GLuint index, GLenum pname, GLdouble * params);
PFNGLGETVERTEXATTRIBLDVPROC _gl_loader_glgetvertexattribldv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint index, GLenum pname, void * * pointer);
PFNGLGETVERTEXATTRIBPOINTERVPROC _gl_loader_glgetvertexattribpointerv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBDVPROC)(GLuint index, GLenum pname, GLdouble * params);
PFNGLGETVERTEXATTRIBDVPROC _gl_loader_glgetvertexattribdv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBFVPROC)(GLuint index, GLenum pname, GLfloat * params);
PFNGLGETVERTEXATTRIBFVPROC _gl_loader_glgetvertexattribfv = NULL;
typedef void (APIENTRY *PFNGLGETVERTEXATTRIBIVPROC)(GLuint index, GLenum pname, GLint * params);
PFNGLGETVERTEXATTRIBIVPROC _gl_loader_glgetvertexattribiv = NULL;
typedef void (APIENTRY *PFNGLGETNCOLORTABLEPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table);
PFNGLGETNCOLORTABLEPROC _gl_loader_glgetncolortable = NULL;
typedef void (APIENTRY *PFNGLGETNCOMPRESSEDTEXIMAGEPROC)(GLenum target, GLint lod, GLsizei bufSize, void * pixels);
PFNGLGETNCOMPRESSEDTEXIMAGEPROC _gl_loader_glgetncompressedteximage = NULL;
typedef void (APIENTRY *PFNGLGETNCONVOLUTIONFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image);
PFNGLGETNCONVOLUTIONFILTERPROC _gl_loader_glgetnconvolutionfilter = NULL;
typedef void (APIENTRY *PFNGLGETNHISTOGRAMPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
PFNGLGETNHISTOGRAMPROC _gl_loader_glgetnhistogram = NULL;
typedef void (APIENTRY *PFNGLGETNMAPDVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v);
PFNGLGETNMAPDVPROC _gl_loader_glgetnmapdv = NULL;
typedef void (APIENTRY *PFNGLGETNMAPFVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v);
PFNGLGETNMAPFVPROC _gl_loader_glgetnmapfv = NULL;
typedef void (APIENTRY *PFNGLGETNMAPIVPROC)(GLenum target, GLenum query, GLsizei bufSize, GLint * v);
PFNGLGETNMAPIVPROC _gl_loader_glgetnmapiv = NULL;
typedef void (APIENTRY *PFNGLGETNMINMAXPROC)(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values);
PFNGLGETNMINMAXPROC _gl_loader_glgetnminmax = NULL;
typedef void (APIENTRY *PFNGLGETNPIXELMAPFVPROC)(GLenum map, GLsizei bufSize, GLfloat * values);
PFNGLGETNPIXELMAPFVPROC _gl_loader_glgetnpixelmapfv = NULL;
typedef void (APIENTRY *PFNGLGETNPIXELMAPUIVPROC)(GLenum map, GLsizei bufSize, GLuint * values);
PFNGLGETNPIXELMAPUIVPROC _gl_loader_glgetnpixelmapuiv = NULL;
typedef void (APIENTRY *PFNGLGETNPIXELMAPUSVPROC)(GLenum map, GLsizei bufSize, GLushort * values);
PFNGLGETNPIXELMAPUSVPROC _gl_loader_glgetnpixelmapusv = NULL;
typedef void (APIENTRY *PFNGLGETNPOLYGONSTIPPLEPROC)(GLsizei bufSize, GLubyte * pattern);
PFNGLGETNPOLYGONSTIPPLEPROC _gl_loader_glgetnpolygonstipple = NULL;
typedef void (APIENTRY *PFNGLGETNSEPARABLEFILTERPROC)(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span);
PFNGLGETNSEPARABLEFILTERPROC _gl_loader_glgetnseparablefilter = NULL;
typedef void (APIENTRY *PFNGLGETNTEXIMAGEPROC)(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels);
PFNGLGETNTEXIMAGEPROC _gl_loader_glgetnteximage = NULL;
typedef void (APIENTRY *PFNGLGETNUNIFORMDVPROC)(GLuint program, GLint location, GLsizei bufSize, GLdouble * params);
PFNGLGETNUNIFORMDVPROC _gl_loader_glgetnuniformdv = NULL;
typedef void (APIENTRY *PFNGLGETNUNIFORMFVPROC)(GLuint program, GLint location, GLsizei bufSize, GLfloat * params);
PFNGLGETNUNIFORMFVPROC _gl_loader_glgetnuniformfv = NULL;
typedef void (APIENTRY *PFNGLGETNUNIFORMIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLint * params);
PFNGLGETNUNIFORMIVPROC _gl_loader_glgetnuniformiv = NULL;
typedef void (APIENTRY *PFNGLGETNUNIFORMUIVPROC)(GLuint program, GLint location, GLsizei bufSize, GLuint * params);
PFNGLGETNUNIFORMUIVPROC _gl_loader_glgetnuniformuiv = NULL;
typedef void (APIENTRY *PFNGLHINTPROC)(GLenum target, GLenum mode);
PFNGLHINTPROC _gl_loader_glhint = NULL;
typedef void (APIENTRY *PFNGLINDEXMASKPROC)(GLuint mask);
PFNGLINDEXMASKPROC _gl_loader_glindexmask = NULL;
typedef void (APIENTRY *PFNGLINDEXPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
PFNGLINDEXPOINTERPROC _gl_loader_glindexpointer = NULL;
typedef void (APIENTRY *PFNGLINDEXDPROC)(GLdouble c);
PFNGLINDEXDPROC _gl_loader_glindexd = NULL;
typedef void (APIENTRY *PFNGLINDEXDVPROC)(const GLdouble * c);
PFNGLINDEXDVPROC _gl_loader_glindexdv = NULL;
typedef void (APIENTRY *PFNGLINDEXFPROC)(GLfloat c);
PFNGLINDEXFPROC _gl_loader_glindexf = NULL;
typedef void (APIENTRY *PFNGLINDEXFVPROC)(const GLfloat * c);
PFNGLINDEXFVPROC _gl_loader_glindexfv = NULL;
typedef void (APIENTRY *PFNGLINDEXIPROC)(GLint c);
PFNGLINDEXIPROC _gl_loader_glindexi = NULL;
typedef void (APIENTRY *PFNGLINDEXIVPROC)(const GLint * c);
PFNGLINDEXIVPROC _gl_loader_glindexiv = NULL;
typedef void (APIENTRY *PFNGLINDEXSPROC)(GLshort c);
PFNGLINDEXSPROC _gl_loader_glindexs = NULL;
typedef void (APIENTRY *PFNGLINDEXSVPROC)(const GLshort * c);
PFNGLINDEXSVPROC _gl_loader_glindexsv = NULL;
typedef void (APIENTRY *PFNGLINDEXUBPROC)(GLubyte c);
PFNGLINDEXUBPROC _gl_loader_glindexub = NULL;
typedef void (APIENTRY *PFNGLINDEXUBVPROC)(const GLubyte * c);
PFNGLINDEXUBVPROC _gl_loader_glindexubv = NULL;
typedef void (APIENTRY *PFNGLINITNAMESPROC)();
PFNGLINITNAMESPROC _gl_loader_glinitnames = NULL;
typedef void (APIENTRY *PFNGLINTERLEAVEDARRAYSPROC)(GLenum format, GLsizei stride, const void * pointer);
PFNGLINTERLEAVEDARRAYSPROC _gl_loader_glinterleavedarrays = NULL;
typedef void (APIENTRY *PFNGLINVALIDATEBUFFERDATAPROC)(GLuint buffer);
PFNGLINVALIDATEBUFFERDATAPROC _gl_loader_glinvalidatebufferdata = NULL;
typedef void (APIENTRY *PFNGLINVALIDATEBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length);
PFNGLINVALIDATEBUFFERSUBDATAPROC _gl_loader_glinvalidatebuffersubdata = NULL;
typedef void (APIENTRY *PFNGLINVALIDATEFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments);
PFNGLINVALIDATEFRAMEBUFFERPROC _gl_loader_glinvalidateframebuffer = NULL;
typedef void (APIENTRY *PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments);
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC _gl_loader_glinvalidatenamedframebufferdata = NULL;
typedef void (APIENTRY *PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC _gl_loader_glinvalidatenamedframebuffersubdata = NULL;
typedef void (APIENTRY *PFNGLINVALIDATESUBFRAMEBUFFERPROC)(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLINVALIDATESUBFRAMEBUFFERPROC _gl_loader_glinvalidatesubframebuffer = NULL;
typedef void (APIENTRY *PFNGLINVALIDATETEXIMAGEPROC)(GLuint texture, GLint level);
PFNGLINVALIDATETEXIMAGEPROC _gl_loader_glinvalidateteximage = NULL;
typedef void (APIENTRY *PFNGLINVALIDATETEXSUBIMAGEPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth);
PFNGLINVALIDATETEXSUBIMAGEPROC _gl_loader_glinvalidatetexsubimage = NULL;
typedef GLboolean (APIENTRY *PFNGLISBUFFERPROC)(GLuint buffer);
PFNGLISBUFFERPROC _gl_loader_glisbuffer = NULL;
typedef GLboolean (APIENTRY *PFNGLISENABLEDPROC)(GLenum cap);
PFNGLISENABLEDPROC _gl_loader_glisenabled = NULL;
typedef GLboolean (APIENTRY *PFNGLISENABLEDIPROC)(GLenum target, GLuint index);
PFNGLISENABLEDIPROC _gl_loader_glisenabledi = NULL;
typedef GLboolean (APIENTRY *PFNGLISFRAMEBUFFERPROC)(GLuint framebuffer);
PFNGLISFRAMEBUFFERPROC _gl_loader_glisframebuffer = NULL;
typedef GLboolean (APIENTRY *PFNGLISLISTPROC)(GLuint list);
PFNGLISLISTPROC _gl_loader_glislist = NULL;
typedef GLboolean (APIENTRY *PFNGLISPROGRAMPROC)(GLuint program);
PFNGLISPROGRAMPROC _gl_loader_glisprogram = NULL;
typedef GLboolean (APIENTRY *PFNGLISPROGRAMPIPELINEPROC)(GLuint pipeline);
PFNGLISPROGRAMPIPELINEPROC _gl_loader_glisprogrampipeline = NULL;
typedef GLboolean (APIENTRY *PFNGLISQUERYPROC)(GLuint id);
PFNGLISQUERYPROC _gl_loader_glisquery = NULL;
typedef GLboolean (APIENTRY *PFNGLISRENDERBUFFERPROC)(GLuint renderbuffer);
PFNGLISRENDERBUFFERPROC _gl_loader_glisrenderbuffer = NULL;
typedef GLboolean (APIENTRY *PFNGLISSAMPLERPROC)(GLuint sampler);
PFNGLISSAMPLERPROC _gl_loader_glissampler = NULL;
typedef GLboolean (APIENTRY *PFNGLISSHADERPROC)(GLuint shader);
PFNGLISSHADERPROC _gl_loader_glisshader = NULL;
typedef GLboolean (APIENTRY *PFNGLISSYNCPROC)(GLsync sync);
PFNGLISSYNCPROC _gl_loader_glissync = NULL;
typedef GLboolean (APIENTRY *PFNGLISTEXTUREPROC)(GLuint texture);
PFNGLISTEXTUREPROC _gl_loader_glistexture = NULL;
typedef GLboolean (APIENTRY *PFNGLISTRANSFORMFEEDBACKPROC)(GLuint id);
PFNGLISTRANSFORMFEEDBACKPROC _gl_loader_glistransformfeedback = NULL;
typedef GLboolean (APIENTRY *PFNGLISVERTEXARRAYPROC)(GLuint array);
PFNGLISVERTEXARRAYPROC _gl_loader_glisvertexarray = NULL;
typedef void (APIENTRY *PFNGLLIGHTMODELFPROC)(GLenum pname, GLfloat param);
PFNGLLIGHTMODELFPROC _gl_loader_gllightmodelf = NULL;
typedef void (APIENTRY *PFNGLLIGHTMODELFVPROC)(GLenum pname, const GLfloat * params);
PFNGLLIGHTMODELFVPROC _gl_loader_gllightmodelfv = NULL;
typedef void (APIENTRY *PFNGLLIGHTMODELIPROC)(GLenum pname, GLint param);
PFNGLLIGHTMODELIPROC _gl_loader_gllightmodeli = NULL;
typedef void (APIENTRY *PFNGLLIGHTMODELIVPROC)(GLenum pname, const GLint * params);
PFNGLLIGHTMODELIVPROC _gl_loader_gllightmodeliv = NULL;
typedef void (APIENTRY *PFNGLLIGHTFPROC)(GLenum light, GLenum pname, GLfloat param);
PFNGLLIGHTFPROC _gl_loader_gllightf = NULL;
typedef void (APIENTRY *PFNGLLIGHTFVPROC)(GLenum light, GLenum pname, const GLfloat * params);
PFNGLLIGHTFVPROC _gl_loader_gllightfv = NULL;
typedef void (APIENTRY *PFNGLLIGHTIPROC)(GLenum light, GLenum pname, GLint param);
PFNGLLIGHTIPROC _gl_loader_gllighti = NULL;
typedef void (APIENTRY *PFNGLLIGHTIVPROC)(GLenum light, GLenum pname, const GLint * params);
PFNGLLIGHTIVPROC _gl_loader_gllightiv = NULL;
typedef void (APIENTRY *PFNGLLINESTIPPLEPROC)(GLint factor, GLushort pattern);
PFNGLLINESTIPPLEPROC _gl_loader_gllinestipple = NULL;
typedef void (APIENTRY *PFNGLLINEWIDTHPROC)(GLfloat width);
PFNGLLINEWIDTHPROC _gl_loader_gllinewidth = NULL;
typedef void (APIENTRY *PFNGLLINKPROGRAMPROC)(GLuint program);
PFNGLLINKPROGRAMPROC _gl_loader_gllinkprogram = NULL;
typedef void (APIENTRY *PFNGLLISTBASEPROC)(GLuint base);
PFNGLLISTBASEPROC _gl_loader_gllistbase = NULL;
typedef void (APIENTRY *PFNGLLOADIDENTITYPROC)();
PFNGLLOADIDENTITYPROC _gl_loader_glloadidentity = NULL;
typedef void (APIENTRY *PFNGLLOADMATRIXDPROC)(const GLdouble * m);
PFNGLLOADMATRIXDPROC _gl_loader_glloadmatrixd = NULL;
typedef void (APIENTRY *PFNGLLOADMATRIXFPROC)(const GLfloat * m);
PFNGLLOADMATRIXFPROC _gl_loader_glloadmatrixf = NULL;
typedef void (APIENTRY *PFNGLLOADNAMEPROC)(GLuint name);
PFNGLLOADNAMEPROC _gl_loader_glloadname = NULL;
typedef void (APIENTRY *PFNGLLOADTRANSPOSEMATRIXDPROC)(const GLdouble * m);
PFNGLLOADTRANSPOSEMATRIXDPROC _gl_loader_glloadtransposematrixd = NULL;
typedef void (APIENTRY *PFNGLLOADTRANSPOSEMATRIXFPROC)(const GLfloat * m);
PFNGLLOADTRANSPOSEMATRIXFPROC _gl_loader_glloadtransposematrixf = NULL;
typedef void (APIENTRY *PFNGLLOGICOPPROC)(GLenum opcode);
PFNGLLOGICOPPROC _gl_loader_gllogicop = NULL;
typedef void (APIENTRY *PFNGLMAP1DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points);
PFNGLMAP1DPROC _gl_loader_glmap1d = NULL;
typedef void (APIENTRY *PFNGLMAP1FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points);
PFNGLMAP1FPROC _gl_loader_glmap1f = NULL;
typedef void (APIENTRY *PFNGLMAP2DPROC)(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points);
PFNGLMAP2DPROC _gl_loader_glmap2d = NULL;
typedef void (APIENTRY *PFNGLMAP2FPROC)(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points);
PFNGLMAP2FPROC _gl_loader_glmap2f = NULL;
typedef void (APIENTRY *PFNGLMAPBUFFERPROC)(GLenum target, GLenum access);
PFNGLMAPBUFFERPROC _gl_loader_glmapbuffer = NULL;
typedef void (APIENTRY *PFNGLMAPBUFFERRANGEPROC)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
PFNGLMAPBUFFERRANGEPROC _gl_loader_glmapbufferrange = NULL;
typedef void (APIENTRY *PFNGLMAPGRID1DPROC)(GLint un, GLdouble u1, GLdouble u2);
PFNGLMAPGRID1DPROC _gl_loader_glmapgrid1d = NULL;
typedef void (APIENTRY *PFNGLMAPGRID1FPROC)(GLint un, GLfloat u1, GLfloat u2);
PFNGLMAPGRID1FPROC _gl_loader_glmapgrid1f = NULL;
typedef void (APIENTRY *PFNGLMAPGRID2DPROC)(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
PFNGLMAPGRID2DPROC _gl_loader_glmapgrid2d = NULL;
typedef void (APIENTRY *PFNGLMAPGRID2FPROC)(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
PFNGLMAPGRID2FPROC _gl_loader_glmapgrid2f = NULL;
typedef void (APIENTRY *PFNGLMAPNAMEDBUFFERPROC)(GLuint buffer, GLenum access);
PFNGLMAPNAMEDBUFFERPROC _gl_loader_glmapnamedbuffer = NULL;
typedef void (APIENTRY *PFNGLMAPNAMEDBUFFERRANGEPROC)(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access);
PFNGLMAPNAMEDBUFFERRANGEPROC _gl_loader_glmapnamedbufferrange = NULL;
typedef void (APIENTRY *PFNGLMATERIALFPROC)(GLenum face, GLenum pname, GLfloat param);
PFNGLMATERIALFPROC _gl_loader_glmaterialf = NULL;
typedef void (APIENTRY *PFNGLMATERIALFVPROC)(GLenum face, GLenum pname, const GLfloat * params);
PFNGLMATERIALFVPROC _gl_loader_glmaterialfv = NULL;
typedef void (APIENTRY *PFNGLMATERIALIPROC)(GLenum face, GLenum pname, GLint param);
PFNGLMATERIALIPROC _gl_loader_glmateriali = NULL;
typedef void (APIENTRY *PFNGLMATERIALIVPROC)(GLenum face, GLenum pname, const GLint * params);
PFNGLMATERIALIVPROC _gl_loader_glmaterialiv = NULL;
typedef void (APIENTRY *PFNGLMATRIXMODEPROC)(GLenum mode);
PFNGLMATRIXMODEPROC _gl_loader_glmatrixmode = NULL;
typedef void (APIENTRY *PFNGLMEMORYBARRIERPROC)(GLbitfield barriers);
PFNGLMEMORYBARRIERPROC _gl_loader_glmemorybarrier = NULL;
typedef void (APIENTRY *PFNGLMEMORYBARRIERBYREGIONPROC)(GLbitfield barriers);
PFNGLMEMORYBARRIERBYREGIONPROC _gl_loader_glmemorybarrierbyregion = NULL;
typedef void (APIENTRY *PFNGLMINSAMPLESHADINGPROC)(GLfloat value);
PFNGLMINSAMPLESHADINGPROC _gl_loader_glminsampleshading = NULL;
typedef void (APIENTRY *PFNGLMULTMATRIXDPROC)(const GLdouble * m);
PFNGLMULTMATRIXDPROC _gl_loader_glmultmatrixd = NULL;
typedef void (APIENTRY *PFNGLMULTMATRIXFPROC)(const GLfloat * m);
PFNGLMULTMATRIXFPROC _gl_loader_glmultmatrixf = NULL;
typedef void (APIENTRY *PFNGLMULTTRANSPOSEMATRIXDPROC)(const GLdouble * m);
PFNGLMULTTRANSPOSEMATRIXDPROC _gl_loader_glmulttransposematrixd = NULL;
typedef void (APIENTRY *PFNGLMULTTRANSPOSEMATRIXFPROC)(const GLfloat * m);
PFNGLMULTTRANSPOSEMATRIXFPROC _gl_loader_glmulttransposematrixf = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWARRAYSPROC)(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount);
PFNGLMULTIDRAWARRAYSPROC _gl_loader_glmultidrawarrays = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWARRAYSINDIRECTPROC)(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride);
PFNGLMULTIDRAWARRAYSINDIRECTPROC _gl_loader_glmultidrawarraysindirect = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)(GLenum mode, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC _gl_loader_glmultidrawarraysindirectcount = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWELEMENTSPROC)(GLenum mode, const GLsizei * count, GLenum type, const void * const * indices, GLsizei drawcount);
PFNGLMULTIDRAWELEMENTSPROC _gl_loader_glmultidrawelements = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)(GLenum mode, const GLsizei * count, GLenum type, const void * const * indices, GLsizei drawcount, const GLint * basevertex);
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC _gl_loader_glmultidrawelementsbasevertex = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWELEMENTSINDIRECTPROC)(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride);
PFNGLMULTIDRAWELEMENTSINDIRECTPROC _gl_loader_glmultidrawelementsindirect = NULL;
typedef void (APIENTRY *PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(GLenum mode, GLenum type, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride);
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC _gl_loader_glmultidrawelementsindirectcount = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1DPROC)(GLenum target, GLdouble s);
PFNGLMULTITEXCOORD1DPROC _gl_loader_glmultitexcoord1d = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1DVPROC)(GLenum target, const GLdouble * v);
PFNGLMULTITEXCOORD1DVPROC _gl_loader_glmultitexcoord1dv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1FPROC)(GLenum target, GLfloat s);
PFNGLMULTITEXCOORD1FPROC _gl_loader_glmultitexcoord1f = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1FVPROC)(GLenum target, const GLfloat * v);
PFNGLMULTITEXCOORD1FVPROC _gl_loader_glmultitexcoord1fv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1IPROC)(GLenum target, GLint s);
PFNGLMULTITEXCOORD1IPROC _gl_loader_glmultitexcoord1i = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1IVPROC)(GLenum target, const GLint * v);
PFNGLMULTITEXCOORD1IVPROC _gl_loader_glmultitexcoord1iv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1SPROC)(GLenum target, GLshort s);
PFNGLMULTITEXCOORD1SPROC _gl_loader_glmultitexcoord1s = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD1SVPROC)(GLenum target, const GLshort * v);
PFNGLMULTITEXCOORD1SVPROC _gl_loader_glmultitexcoord1sv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2DPROC)(GLenum target, GLdouble s, GLdouble t);
PFNGLMULTITEXCOORD2DPROC _gl_loader_glmultitexcoord2d = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2DVPROC)(GLenum target, const GLdouble * v);
PFNGLMULTITEXCOORD2DVPROC _gl_loader_glmultitexcoord2dv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2FPROC)(GLenum target, GLfloat s, GLfloat t);
PFNGLMULTITEXCOORD2FPROC _gl_loader_glmultitexcoord2f = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2FVPROC)(GLenum target, const GLfloat * v);
PFNGLMULTITEXCOORD2FVPROC _gl_loader_glmultitexcoord2fv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2IPROC)(GLenum target, GLint s, GLint t);
PFNGLMULTITEXCOORD2IPROC _gl_loader_glmultitexcoord2i = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2IVPROC)(GLenum target, const GLint * v);
PFNGLMULTITEXCOORD2IVPROC _gl_loader_glmultitexcoord2iv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2SPROC)(GLenum target, GLshort s, GLshort t);
PFNGLMULTITEXCOORD2SPROC _gl_loader_glmultitexcoord2s = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD2SVPROC)(GLenum target, const GLshort * v);
PFNGLMULTITEXCOORD2SVPROC _gl_loader_glmultitexcoord2sv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r);
PFNGLMULTITEXCOORD3DPROC _gl_loader_glmultitexcoord3d = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3DVPROC)(GLenum target, const GLdouble * v);
PFNGLMULTITEXCOORD3DVPROC _gl_loader_glmultitexcoord3dv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r);
PFNGLMULTITEXCOORD3FPROC _gl_loader_glmultitexcoord3f = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3FVPROC)(GLenum target, const GLfloat * v);
PFNGLMULTITEXCOORD3FVPROC _gl_loader_glmultitexcoord3fv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3IPROC)(GLenum target, GLint s, GLint t, GLint r);
PFNGLMULTITEXCOORD3IPROC _gl_loader_glmultitexcoord3i = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3IVPROC)(GLenum target, const GLint * v);
PFNGLMULTITEXCOORD3IVPROC _gl_loader_glmultitexcoord3iv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3SPROC)(GLenum target, GLshort s, GLshort t, GLshort r);
PFNGLMULTITEXCOORD3SPROC _gl_loader_glmultitexcoord3s = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD3SVPROC)(GLenum target, const GLshort * v);
PFNGLMULTITEXCOORD3SVPROC _gl_loader_glmultitexcoord3sv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4DPROC)(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q);
PFNGLMULTITEXCOORD4DPROC _gl_loader_glmultitexcoord4d = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4DVPROC)(GLenum target, const GLdouble * v);
PFNGLMULTITEXCOORD4DVPROC _gl_loader_glmultitexcoord4dv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4FPROC)(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
PFNGLMULTITEXCOORD4FPROC _gl_loader_glmultitexcoord4f = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4FVPROC)(GLenum target, const GLfloat * v);
PFNGLMULTITEXCOORD4FVPROC _gl_loader_glmultitexcoord4fv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4IPROC)(GLenum target, GLint s, GLint t, GLint r, GLint q);
PFNGLMULTITEXCOORD4IPROC _gl_loader_glmultitexcoord4i = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4IVPROC)(GLenum target, const GLint * v);
PFNGLMULTITEXCOORD4IVPROC _gl_loader_glmultitexcoord4iv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4SPROC)(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q);
PFNGLMULTITEXCOORD4SPROC _gl_loader_glmultitexcoord4s = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORD4SVPROC)(GLenum target, const GLshort * v);
PFNGLMULTITEXCOORD4SVPROC _gl_loader_glmultitexcoord4sv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP1UIPROC)(GLenum texture, GLenum type, GLuint coords);
PFNGLMULTITEXCOORDP1UIPROC _gl_loader_glmultitexcoordp1ui = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP1UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
PFNGLMULTITEXCOORDP1UIVPROC _gl_loader_glmultitexcoordp1uiv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP2UIPROC)(GLenum texture, GLenum type, GLuint coords);
PFNGLMULTITEXCOORDP2UIPROC _gl_loader_glmultitexcoordp2ui = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP2UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
PFNGLMULTITEXCOORDP2UIVPROC _gl_loader_glmultitexcoordp2uiv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP3UIPROC)(GLenum texture, GLenum type, GLuint coords);
PFNGLMULTITEXCOORDP3UIPROC _gl_loader_glmultitexcoordp3ui = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP3UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
PFNGLMULTITEXCOORDP3UIVPROC _gl_loader_glmultitexcoordp3uiv = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP4UIPROC)(GLenum texture, GLenum type, GLuint coords);
PFNGLMULTITEXCOORDP4UIPROC _gl_loader_glmultitexcoordp4ui = NULL;
typedef void (APIENTRY *PFNGLMULTITEXCOORDP4UIVPROC)(GLenum texture, GLenum type, const GLuint * coords);
PFNGLMULTITEXCOORDP4UIVPROC _gl_loader_glmultitexcoordp4uiv = NULL;
typedef void (APIENTRY *PFNGLNAMEDBUFFERDATAPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage);
PFNGLNAMEDBUFFERDATAPROC _gl_loader_glnamedbufferdata = NULL;
typedef void (APIENTRY *PFNGLNAMEDBUFFERSTORAGEPROC)(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags);
PFNGLNAMEDBUFFERSTORAGEPROC _gl_loader_glnamedbufferstorage = NULL;
typedef void (APIENTRY *PFNGLNAMEDBUFFERSUBDATAPROC)(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data);
PFNGLNAMEDBUFFERSUBDATAPROC _gl_loader_glnamedbuffersubdata = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)(GLuint framebuffer, GLenum buf);
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC _gl_loader_glnamedframebufferdrawbuffer = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)(GLuint framebuffer, GLsizei n, const GLenum * bufs);
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC _gl_loader_glnamedframebufferdrawbuffers = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)(GLuint framebuffer, GLenum pname, GLint param);
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC _gl_loader_glnamedframebufferparameteri = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)(GLuint framebuffer, GLenum src);
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC _gl_loader_glnamedframebufferreadbuffer = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC _gl_loader_glnamedframebufferrenderbuffer = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level);
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC _gl_loader_glnamedframebuffertexture = NULL;
typedef void (APIENTRY *PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer);
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC _gl_loader_glnamedframebuffertexturelayer = NULL;
typedef void (APIENTRY *PFNGLNAMEDRENDERBUFFERSTORAGEPROC)(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLNAMEDRENDERBUFFERSTORAGEPROC _gl_loader_glnamedrenderbufferstorage = NULL;
typedef void (APIENTRY *PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC _gl_loader_glnamedrenderbufferstoragemultisample = NULL;
typedef void (APIENTRY *PFNGLNEWLISTPROC)(GLuint list, GLenum mode);
PFNGLNEWLISTPROC _gl_loader_glnewlist = NULL;
typedef void (APIENTRY *PFNGLNORMAL3BPROC)(GLbyte nx, GLbyte ny, GLbyte nz);
PFNGLNORMAL3BPROC _gl_loader_glnormal3b = NULL;
typedef void (APIENTRY *PFNGLNORMAL3BVPROC)(const GLbyte * v);
PFNGLNORMAL3BVPROC _gl_loader_glnormal3bv = NULL;
typedef void (APIENTRY *PFNGLNORMAL3DPROC)(GLdouble nx, GLdouble ny, GLdouble nz);
PFNGLNORMAL3DPROC _gl_loader_glnormal3d = NULL;
typedef void (APIENTRY *PFNGLNORMAL3DVPROC)(const GLdouble * v);
PFNGLNORMAL3DVPROC _gl_loader_glnormal3dv = NULL;
typedef void (APIENTRY *PFNGLNORMAL3FPROC)(GLfloat nx, GLfloat ny, GLfloat nz);
PFNGLNORMAL3FPROC _gl_loader_glnormal3f = NULL;
typedef void (APIENTRY *PFNGLNORMAL3FVPROC)(const GLfloat * v);
PFNGLNORMAL3FVPROC _gl_loader_glnormal3fv = NULL;
typedef void (APIENTRY *PFNGLNORMAL3IPROC)(GLint nx, GLint ny, GLint nz);
PFNGLNORMAL3IPROC _gl_loader_glnormal3i = NULL;
typedef void (APIENTRY *PFNGLNORMAL3IVPROC)(const GLint * v);
PFNGLNORMAL3IVPROC _gl_loader_glnormal3iv = NULL;
typedef void (APIENTRY *PFNGLNORMAL3SPROC)(GLshort nx, GLshort ny, GLshort nz);
PFNGLNORMAL3SPROC _gl_loader_glnormal3s = NULL;
typedef void (APIENTRY *PFNGLNORMAL3SVPROC)(const GLshort * v);
PFNGLNORMAL3SVPROC _gl_loader_glnormal3sv = NULL;
typedef void (APIENTRY *PFNGLNORMALP3UIPROC)(GLenum type, GLuint coords);
PFNGLNORMALP3UIPROC _gl_loader_glnormalp3ui = NULL;
typedef void (APIENTRY *PFNGLNORMALP3UIVPROC)(GLenum type, const GLuint * coords);
PFNGLNORMALP3UIVPROC _gl_loader_glnormalp3uiv = NULL;
typedef void (APIENTRY *PFNGLNORMALPOINTERPROC)(GLenum type, GLsizei stride, const void * pointer);
PFNGLNORMALPOINTERPROC _gl_loader_glnormalpointer = NULL;
typedef void (APIENTRY *PFNGLOBJECTLABELPROC)(GLenum identifier, GLuint name, GLsizei length, const GLchar * label);
PFNGLOBJECTLABELPROC _gl_loader_globjectlabel = NULL;
typedef void (APIENTRY *PFNGLOBJECTPTRLABELPROC)(const void * ptr, GLsizei length, const GLchar * label);
PFNGLOBJECTPTRLABELPROC _gl_loader_globjectptrlabel = NULL;
typedef void (APIENTRY *PFNGLORTHOPROC)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
PFNGLORTHOPROC _gl_loader_glortho = NULL;
typedef void (APIENTRY *PFNGLPASSTHROUGHPROC)(GLfloat token);
PFNGLPASSTHROUGHPROC _gl_loader_glpassthrough = NULL;
typedef void (APIENTRY *PFNGLPATCHPARAMETERFVPROC)(GLenum pname, const GLfloat * values);
PFNGLPATCHPARAMETERFVPROC _gl_loader_glpatchparameterfv = NULL;
typedef void (APIENTRY *PFNGLPATCHPARAMETERIPROC)(GLenum pname, GLint value);
PFNGLPATCHPARAMETERIPROC _gl_loader_glpatchparameteri = NULL;
typedef void (APIENTRY *PFNGLPAUSETRANSFORMFEEDBACKPROC)();
PFNGLPAUSETRANSFORMFEEDBACKPROC _gl_loader_glpausetransformfeedback = NULL;
typedef void (APIENTRY *PFNGLPIXELMAPFVPROC)(GLenum map, GLsizei mapsize, const GLfloat * values);
PFNGLPIXELMAPFVPROC _gl_loader_glpixelmapfv = NULL;
typedef void (APIENTRY *PFNGLPIXELMAPUIVPROC)(GLenum map, GLsizei mapsize, const GLuint * values);
PFNGLPIXELMAPUIVPROC _gl_loader_glpixelmapuiv = NULL;
typedef void (APIENTRY *PFNGLPIXELMAPUSVPROC)(GLenum map, GLsizei mapsize, const GLushort * values);
PFNGLPIXELMAPUSVPROC _gl_loader_glpixelmapusv = NULL;
typedef void (APIENTRY *PFNGLPIXELSTOREFPROC)(GLenum pname, GLfloat param);
PFNGLPIXELSTOREFPROC _gl_loader_glpixelstoref = NULL;
typedef void (APIENTRY *PFNGLPIXELSTOREIPROC)(GLenum pname, GLint param);
PFNGLPIXELSTOREIPROC _gl_loader_glpixelstorei = NULL;
typedef void (APIENTRY *PFNGLPIXELTRANSFERFPROC)(GLenum pname, GLfloat param);
PFNGLPIXELTRANSFERFPROC _gl_loader_glpixeltransferf = NULL;
typedef void (APIENTRY *PFNGLPIXELTRANSFERIPROC)(GLenum pname, GLint param);
PFNGLPIXELTRANSFERIPROC _gl_loader_glpixeltransferi = NULL;
typedef void (APIENTRY *PFNGLPIXELZOOMPROC)(GLfloat xfactor, GLfloat yfactor);
PFNGLPIXELZOOMPROC _gl_loader_glpixelzoom = NULL;
typedef void (APIENTRY *PFNGLPOINTPARAMETERFPROC)(GLenum pname, GLfloat param);
PFNGLPOINTPARAMETERFPROC _gl_loader_glpointparameterf = NULL;
typedef void (APIENTRY *PFNGLPOINTPARAMETERFVPROC)(GLenum pname, const GLfloat * params);
PFNGLPOINTPARAMETERFVPROC _gl_loader_glpointparameterfv = NULL;
typedef void (APIENTRY *PFNGLPOINTPARAMETERIPROC)(GLenum pname, GLint param);
PFNGLPOINTPARAMETERIPROC _gl_loader_glpointparameteri = NULL;
typedef void (APIENTRY *PFNGLPOINTPARAMETERIVPROC)(GLenum pname, const GLint * params);
PFNGLPOINTPARAMETERIVPROC _gl_loader_glpointparameteriv = NULL;
typedef void (APIENTRY *PFNGLPOINTSIZEPROC)(GLfloat size);
PFNGLPOINTSIZEPROC _gl_loader_glpointsize = NULL;
typedef void (APIENTRY *PFNGLPOLYGONMODEPROC)(GLenum face, GLenum mode);
PFNGLPOLYGONMODEPROC _gl_loader_glpolygonmode = NULL;
typedef void (APIENTRY *PFNGLPOLYGONOFFSETPROC)(GLfloat factor, GLfloat units);
PFNGLPOLYGONOFFSETPROC _gl_loader_glpolygonoffset = NULL;
typedef void (APIENTRY *PFNGLPOLYGONOFFSETCLAMPPROC)(GLfloat factor, GLfloat units, GLfloat clamp);
PFNGLPOLYGONOFFSETCLAMPPROC _gl_loader_glpolygonoffsetclamp = NULL;
typedef void (APIENTRY *PFNGLPOLYGONSTIPPLEPROC)(const GLubyte * mask);
PFNGLPOLYGONSTIPPLEPROC _gl_loader_glpolygonstipple = NULL;
typedef void (APIENTRY *PFNGLPOPATTRIBPROC)();
PFNGLPOPATTRIBPROC _gl_loader_glpopattrib = NULL;
typedef void (APIENTRY *PFNGLPOPCLIENTATTRIBPROC)();
PFNGLPOPCLIENTATTRIBPROC _gl_loader_glpopclientattrib = NULL;
typedef void (APIENTRY *PFNGLPOPDEBUGGROUPPROC)();
PFNGLPOPDEBUGGROUPPROC _gl_loader_glpopdebuggroup = NULL;
typedef void (APIENTRY *PFNGLPOPMATRIXPROC)();
PFNGLPOPMATRIXPROC _gl_loader_glpopmatrix = NULL;
typedef void (APIENTRY *PFNGLPOPNAMEPROC)();
PFNGLPOPNAMEPROC _gl_loader_glpopname = NULL;
typedef void (APIENTRY *PFNGLPRIMITIVERESTARTINDEXPROC)(GLuint index);
PFNGLPRIMITIVERESTARTINDEXPROC _gl_loader_glprimitiverestartindex = NULL;
typedef void (APIENTRY *PFNGLPRIORITIZETEXTURESPROC)(GLsizei n, const GLuint * textures, const GLfloat * priorities);
PFNGLPRIORITIZETEXTURESPROC _gl_loader_glprioritizetextures = NULL;
typedef void (APIENTRY *PFNGLPROGRAMBINARYPROC)(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length);
PFNGLPROGRAMBINARYPROC _gl_loader_glprogrambinary = NULL;
typedef void (APIENTRY *PFNGLPROGRAMPARAMETERIPROC)(GLuint program, GLenum pname, GLint value);
PFNGLPROGRAMPARAMETERIPROC _gl_loader_glprogramparameteri = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1DPROC)(GLuint program, GLint location, GLdouble v0);
PFNGLPROGRAMUNIFORM1DPROC _gl_loader_glprogramuniform1d = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
PFNGLPROGRAMUNIFORM1DVPROC _gl_loader_glprogramuniform1dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1FPROC)(GLuint program, GLint location, GLfloat v0);
PFNGLPROGRAMUNIFORM1FPROC _gl_loader_glprogramuniform1f = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
PFNGLPROGRAMUNIFORM1FVPROC _gl_loader_glprogramuniform1fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1IPROC)(GLuint program, GLint location, GLint v0);
PFNGLPROGRAMUNIFORM1IPROC _gl_loader_glprogramuniform1i = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
PFNGLPROGRAMUNIFORM1IVPROC _gl_loader_glprogramuniform1iv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1UIPROC)(GLuint program, GLint location, GLuint v0);
PFNGLPROGRAMUNIFORM1UIPROC _gl_loader_glprogramuniform1ui = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM1UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
PFNGLPROGRAMUNIFORM1UIVPROC _gl_loader_glprogramuniform1uiv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1);
PFNGLPROGRAMUNIFORM2DPROC _gl_loader_glprogramuniform2d = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
PFNGLPROGRAMUNIFORM2DVPROC _gl_loader_glprogramuniform2dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1);
PFNGLPROGRAMUNIFORM2FPROC _gl_loader_glprogramuniform2f = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
PFNGLPROGRAMUNIFORM2FVPROC _gl_loader_glprogramuniform2fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2IPROC)(GLuint program, GLint location, GLint v0, GLint v1);
PFNGLPROGRAMUNIFORM2IPROC _gl_loader_glprogramuniform2i = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
PFNGLPROGRAMUNIFORM2IVPROC _gl_loader_glprogramuniform2iv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1);
PFNGLPROGRAMUNIFORM2UIPROC _gl_loader_glprogramuniform2ui = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM2UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
PFNGLPROGRAMUNIFORM2UIVPROC _gl_loader_glprogramuniform2uiv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2);
PFNGLPROGRAMUNIFORM3DPROC _gl_loader_glprogramuniform3d = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
PFNGLPROGRAMUNIFORM3DVPROC _gl_loader_glprogramuniform3dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
PFNGLPROGRAMUNIFORM3FPROC _gl_loader_glprogramuniform3f = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
PFNGLPROGRAMUNIFORM3FVPROC _gl_loader_glprogramuniform3fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2);
PFNGLPROGRAMUNIFORM3IPROC _gl_loader_glprogramuniform3i = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
PFNGLPROGRAMUNIFORM3IVPROC _gl_loader_glprogramuniform3iv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2);
PFNGLPROGRAMUNIFORM3UIPROC _gl_loader_glprogramuniform3ui = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM3UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
PFNGLPROGRAMUNIFORM3UIVPROC _gl_loader_glprogramuniform3uiv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4DPROC)(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3);
PFNGLPROGRAMUNIFORM4DPROC _gl_loader_glprogramuniform4d = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4DVPROC)(GLuint program, GLint location, GLsizei count, const GLdouble * value);
PFNGLPROGRAMUNIFORM4DVPROC _gl_loader_glprogramuniform4dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4FPROC)(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
PFNGLPROGRAMUNIFORM4FPROC _gl_loader_glprogramuniform4f = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4FVPROC)(GLuint program, GLint location, GLsizei count, const GLfloat * value);
PFNGLPROGRAMUNIFORM4FVPROC _gl_loader_glprogramuniform4fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4IPROC)(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
PFNGLPROGRAMUNIFORM4IPROC _gl_loader_glprogramuniform4i = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4IVPROC)(GLuint program, GLint location, GLsizei count, const GLint * value);
PFNGLPROGRAMUNIFORM4IVPROC _gl_loader_glprogramuniform4iv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4UIPROC)(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
PFNGLPROGRAMUNIFORM4UIPROC _gl_loader_glprogramuniform4ui = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORM4UIVPROC)(GLuint program, GLint location, GLsizei count, const GLuint * value);
PFNGLPROGRAMUNIFORM4UIVPROC _gl_loader_glprogramuniform4uiv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX2DVPROC _gl_loader_glprogramuniformmatrix2dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX2FVPROC _gl_loader_glprogramuniformmatrix2fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC _gl_loader_glprogramuniformmatrix2x3dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC _gl_loader_glprogramuniformmatrix2x3fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC _gl_loader_glprogramuniformmatrix2x4dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC _gl_loader_glprogramuniformmatrix2x4fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX3DVPROC _gl_loader_glprogramuniformmatrix3dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX3FVPROC _gl_loader_glprogramuniformmatrix3fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC _gl_loader_glprogramuniformmatrix3x2dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC _gl_loader_glprogramuniformmatrix3x2fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC _gl_loader_glprogramuniformmatrix3x4dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC _gl_loader_glprogramuniformmatrix3x4fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX4DVPROC _gl_loader_glprogramuniformmatrix4dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX4FVPROC _gl_loader_glprogramuniformmatrix4fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC _gl_loader_glprogramuniformmatrix4x2dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC _gl_loader_glprogramuniformmatrix4x2fv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC _gl_loader_glprogramuniformmatrix4x3dv = NULL;
typedef void (APIENTRY *PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC _gl_loader_glprogramuniformmatrix4x3fv = NULL;
typedef void (APIENTRY *PFNGLPROVOKINGVERTEXPROC)(GLenum mode);
PFNGLPROVOKINGVERTEXPROC _gl_loader_glprovokingvertex = NULL;
typedef void (APIENTRY *PFNGLPUSHATTRIBPROC)(GLbitfield mask);
PFNGLPUSHATTRIBPROC _gl_loader_glpushattrib = NULL;
typedef void (APIENTRY *PFNGLPUSHCLIENTATTRIBPROC)(GLbitfield mask);
PFNGLPUSHCLIENTATTRIBPROC _gl_loader_glpushclientattrib = NULL;
typedef void (APIENTRY *PFNGLPUSHDEBUGGROUPPROC)(GLenum source, GLuint id, GLsizei length, const GLchar * message);
PFNGLPUSHDEBUGGROUPPROC _gl_loader_glpushdebuggroup = NULL;
typedef void (APIENTRY *PFNGLPUSHMATRIXPROC)();
PFNGLPUSHMATRIXPROC _gl_loader_glpushmatrix = NULL;
typedef void (APIENTRY *PFNGLPUSHNAMEPROC)(GLuint name);
PFNGLPUSHNAMEPROC _gl_loader_glpushname = NULL;
typedef void (APIENTRY *PFNGLQUERYCOUNTERPROC)(GLuint id, GLenum target);
PFNGLQUERYCOUNTERPROC _gl_loader_glquerycounter = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2DPROC)(GLdouble x, GLdouble y);
PFNGLRASTERPOS2DPROC _gl_loader_glrasterpos2d = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2DVPROC)(const GLdouble * v);
PFNGLRASTERPOS2DVPROC _gl_loader_glrasterpos2dv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2FPROC)(GLfloat x, GLfloat y);
PFNGLRASTERPOS2FPROC _gl_loader_glrasterpos2f = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2FVPROC)(const GLfloat * v);
PFNGLRASTERPOS2FVPROC _gl_loader_glrasterpos2fv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2IPROC)(GLint x, GLint y);
PFNGLRASTERPOS2IPROC _gl_loader_glrasterpos2i = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2IVPROC)(const GLint * v);
PFNGLRASTERPOS2IVPROC _gl_loader_glrasterpos2iv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2SPROC)(GLshort x, GLshort y);
PFNGLRASTERPOS2SPROC _gl_loader_glrasterpos2s = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS2SVPROC)(const GLshort * v);
PFNGLRASTERPOS2SVPROC _gl_loader_glrasterpos2sv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLRASTERPOS3DPROC _gl_loader_glrasterpos3d = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3DVPROC)(const GLdouble * v);
PFNGLRASTERPOS3DVPROC _gl_loader_glrasterpos3dv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLRASTERPOS3FPROC _gl_loader_glrasterpos3f = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3FVPROC)(const GLfloat * v);
PFNGLRASTERPOS3FVPROC _gl_loader_glrasterpos3fv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3IPROC)(GLint x, GLint y, GLint z);
PFNGLRASTERPOS3IPROC _gl_loader_glrasterpos3i = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3IVPROC)(const GLint * v);
PFNGLRASTERPOS3IVPROC _gl_loader_glrasterpos3iv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLRASTERPOS3SPROC _gl_loader_glrasterpos3s = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS3SVPROC)(const GLshort * v);
PFNGLRASTERPOS3SVPROC _gl_loader_glrasterpos3sv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLRASTERPOS4DPROC _gl_loader_glrasterpos4d = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4DVPROC)(const GLdouble * v);
PFNGLRASTERPOS4DVPROC _gl_loader_glrasterpos4dv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLRASTERPOS4FPROC _gl_loader_glrasterpos4f = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4FVPROC)(const GLfloat * v);
PFNGLRASTERPOS4FVPROC _gl_loader_glrasterpos4fv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4IPROC)(GLint x, GLint y, GLint z, GLint w);
PFNGLRASTERPOS4IPROC _gl_loader_glrasterpos4i = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4IVPROC)(const GLint * v);
PFNGLRASTERPOS4IVPROC _gl_loader_glrasterpos4iv = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLRASTERPOS4SPROC _gl_loader_glrasterpos4s = NULL;
typedef void (APIENTRY *PFNGLRASTERPOS4SVPROC)(const GLshort * v);
PFNGLRASTERPOS4SVPROC _gl_loader_glrasterpos4sv = NULL;
typedef void (APIENTRY *PFNGLREADBUFFERPROC)(GLenum src);
PFNGLREADBUFFERPROC _gl_loader_glreadbuffer = NULL;
typedef void (APIENTRY *PFNGLREADPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
PFNGLREADPIXELSPROC _gl_loader_glreadpixels = NULL;
typedef void (APIENTRY *PFNGLREADNPIXELSPROC)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data);
PFNGLREADNPIXELSPROC _gl_loader_glreadnpixels = NULL;
typedef void (APIENTRY *PFNGLRECTDPROC)(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
PFNGLRECTDPROC _gl_loader_glrectd = NULL;
typedef void (APIENTRY *PFNGLRECTDVPROC)(const GLdouble * v1, const GLdouble * v2);
PFNGLRECTDVPROC _gl_loader_glrectdv = NULL;
typedef void (APIENTRY *PFNGLRECTFPROC)(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
PFNGLRECTFPROC _gl_loader_glrectf = NULL;
typedef void (APIENTRY *PFNGLRECTFVPROC)(const GLfloat * v1, const GLfloat * v2);
PFNGLRECTFVPROC _gl_loader_glrectfv = NULL;
typedef void (APIENTRY *PFNGLRECTIPROC)(GLint x1, GLint y1, GLint x2, GLint y2);
PFNGLRECTIPROC _gl_loader_glrecti = NULL;
typedef void (APIENTRY *PFNGLRECTIVPROC)(const GLint * v1, const GLint * v2);
PFNGLRECTIVPROC _gl_loader_glrectiv = NULL;
typedef void (APIENTRY *PFNGLRECTSPROC)(GLshort x1, GLshort y1, GLshort x2, GLshort y2);
PFNGLRECTSPROC _gl_loader_glrects = NULL;
typedef void (APIENTRY *PFNGLRECTSVPROC)(const GLshort * v1, const GLshort * v2);
PFNGLRECTSVPROC _gl_loader_glrectsv = NULL;
typedef void (APIENTRY *PFNGLRELEASESHADERCOMPILERPROC)();
PFNGLRELEASESHADERCOMPILERPROC _gl_loader_glreleaseshadercompiler = NULL;
typedef GLint (APIENTRY *PFNGLRENDERMODEPROC)(GLenum mode);
PFNGLRENDERMODEPROC _gl_loader_glrendermode = NULL;
typedef void (APIENTRY *PFNGLRENDERBUFFERSTORAGEPROC)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLRENDERBUFFERSTORAGEPROC _gl_loader_glrenderbufferstorage = NULL;
typedef void (APIENTRY *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC _gl_loader_glrenderbufferstoragemultisample = NULL;
typedef void (APIENTRY *PFNGLRESUMETRANSFORMFEEDBACKPROC)();
PFNGLRESUMETRANSFORMFEEDBACKPROC _gl_loader_glresumetransformfeedback = NULL;
typedef void (APIENTRY *PFNGLROTATEDPROC)(GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
PFNGLROTATEDPROC _gl_loader_glrotated = NULL;
typedef void (APIENTRY *PFNGLROTATEFPROC)(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
PFNGLROTATEFPROC _gl_loader_glrotatef = NULL;
typedef void (APIENTRY *PFNGLSAMPLECOVERAGEPROC)(GLfloat value, GLboolean invert);
PFNGLSAMPLECOVERAGEPROC _gl_loader_glsamplecoverage = NULL;
typedef void (APIENTRY *PFNGLSAMPLEMASKIPROC)(GLuint maskNumber, GLbitfield mask);
PFNGLSAMPLEMASKIPROC _gl_loader_glsamplemaski = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERIIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
PFNGLSAMPLERPARAMETERIIVPROC _gl_loader_glsamplerparameteriiv = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERIUIVPROC)(GLuint sampler, GLenum pname, const GLuint * param);
PFNGLSAMPLERPARAMETERIUIVPROC _gl_loader_glsamplerparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERFPROC)(GLuint sampler, GLenum pname, GLfloat param);
PFNGLSAMPLERPARAMETERFPROC _gl_loader_glsamplerparameterf = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERFVPROC)(GLuint sampler, GLenum pname, const GLfloat * param);
PFNGLSAMPLERPARAMETERFVPROC _gl_loader_glsamplerparameterfv = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERIPROC)(GLuint sampler, GLenum pname, GLint param);
PFNGLSAMPLERPARAMETERIPROC _gl_loader_glsamplerparameteri = NULL;
typedef void (APIENTRY *PFNGLSAMPLERPARAMETERIVPROC)(GLuint sampler, GLenum pname, const GLint * param);
PFNGLSAMPLERPARAMETERIVPROC _gl_loader_glsamplerparameteriv = NULL;
typedef void (APIENTRY *PFNGLSCALEDPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLSCALEDPROC _gl_loader_glscaled = NULL;
typedef void (APIENTRY *PFNGLSCALEFPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLSCALEFPROC _gl_loader_glscalef = NULL;
typedef void (APIENTRY *PFNGLSCISSORPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLSCISSORPROC _gl_loader_glscissor = NULL;
typedef void (APIENTRY *PFNGLSCISSORARRAYVPROC)(GLuint first, GLsizei count, const GLint * v);
PFNGLSCISSORARRAYVPROC _gl_loader_glscissorarrayv = NULL;
typedef void (APIENTRY *PFNGLSCISSORINDEXEDPROC)(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height);
PFNGLSCISSORINDEXEDPROC _gl_loader_glscissorindexed = NULL;
typedef void (APIENTRY *PFNGLSCISSORINDEXEDVPROC)(GLuint index, const GLint * v);
PFNGLSCISSORINDEXEDVPROC _gl_loader_glscissorindexedv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3BPROC)(GLbyte red, GLbyte green, GLbyte blue);
PFNGLSECONDARYCOLOR3BPROC _gl_loader_glsecondarycolor3b = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3BVPROC)(const GLbyte * v);
PFNGLSECONDARYCOLOR3BVPROC _gl_loader_glsecondarycolor3bv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3DPROC)(GLdouble red, GLdouble green, GLdouble blue);
PFNGLSECONDARYCOLOR3DPROC _gl_loader_glsecondarycolor3d = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3DVPROC)(const GLdouble * v);
PFNGLSECONDARYCOLOR3DVPROC _gl_loader_glsecondarycolor3dv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3FPROC)(GLfloat red, GLfloat green, GLfloat blue);
PFNGLSECONDARYCOLOR3FPROC _gl_loader_glsecondarycolor3f = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3FVPROC)(const GLfloat * v);
PFNGLSECONDARYCOLOR3FVPROC _gl_loader_glsecondarycolor3fv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3IPROC)(GLint red, GLint green, GLint blue);
PFNGLSECONDARYCOLOR3IPROC _gl_loader_glsecondarycolor3i = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3IVPROC)(const GLint * v);
PFNGLSECONDARYCOLOR3IVPROC _gl_loader_glsecondarycolor3iv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3SPROC)(GLshort red, GLshort green, GLshort blue);
PFNGLSECONDARYCOLOR3SPROC _gl_loader_glsecondarycolor3s = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3SVPROC)(const GLshort * v);
PFNGLSECONDARYCOLOR3SVPROC _gl_loader_glsecondarycolor3sv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3UBPROC)(GLubyte red, GLubyte green, GLubyte blue);
PFNGLSECONDARYCOLOR3UBPROC _gl_loader_glsecondarycolor3ub = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3UBVPROC)(const GLubyte * v);
PFNGLSECONDARYCOLOR3UBVPROC _gl_loader_glsecondarycolor3ubv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3UIPROC)(GLuint red, GLuint green, GLuint blue);
PFNGLSECONDARYCOLOR3UIPROC _gl_loader_glsecondarycolor3ui = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3UIVPROC)(const GLuint * v);
PFNGLSECONDARYCOLOR3UIVPROC _gl_loader_glsecondarycolor3uiv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3USPROC)(GLushort red, GLushort green, GLushort blue);
PFNGLSECONDARYCOLOR3USPROC _gl_loader_glsecondarycolor3us = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLOR3USVPROC)(const GLushort * v);
PFNGLSECONDARYCOLOR3USVPROC _gl_loader_glsecondarycolor3usv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLORP3UIPROC)(GLenum type, GLuint color);
PFNGLSECONDARYCOLORP3UIPROC _gl_loader_glsecondarycolorp3ui = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLORP3UIVPROC)(GLenum type, const GLuint * color);
PFNGLSECONDARYCOLORP3UIVPROC _gl_loader_glsecondarycolorp3uiv = NULL;
typedef void (APIENTRY *PFNGLSECONDARYCOLORPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLSECONDARYCOLORPOINTERPROC _gl_loader_glsecondarycolorpointer = NULL;
typedef void (APIENTRY *PFNGLSELECTBUFFERPROC)(GLsizei size, GLuint * buffer);
PFNGLSELECTBUFFERPROC _gl_loader_glselectbuffer = NULL;
typedef void (APIENTRY *PFNGLSHADEMODELPROC)(GLenum mode);
PFNGLSHADEMODELPROC _gl_loader_glshademodel = NULL;
typedef void (APIENTRY *PFNGLSHADERBINARYPROC)(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void * binary, GLsizei length);
PFNGLSHADERBINARYPROC _gl_loader_glshaderbinary = NULL;
typedef void (APIENTRY *PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar * const * string, const GLint * length);
PFNGLSHADERSOURCEPROC _gl_loader_glshadersource = NULL;
typedef void (APIENTRY *PFNGLSHADERSTORAGEBLOCKBINDINGPROC)(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding);
PFNGLSHADERSTORAGEBLOCKBINDINGPROC _gl_loader_glshaderstorageblockbinding = NULL;
typedef void (APIENTRY *PFNGLSPECIALIZESHADERPROC)(GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue);
PFNGLSPECIALIZESHADERPROC _gl_loader_glspecializeshader = NULL;
typedef void (APIENTRY *PFNGLSTENCILFUNCPROC)(GLenum func, GLint ref, GLuint mask);
PFNGLSTENCILFUNCPROC _gl_loader_glstencilfunc = NULL;
typedef void (APIENTRY *PFNGLSTENCILFUNCSEPARATEPROC)(GLenum face, GLenum func, GLint ref, GLuint mask);
PFNGLSTENCILFUNCSEPARATEPROC _gl_loader_glstencilfuncseparate = NULL;
typedef void (APIENTRY *PFNGLSTENCILMASKPROC)(GLuint mask);
PFNGLSTENCILMASKPROC _gl_loader_glstencilmask = NULL;
typedef void (APIENTRY *PFNGLSTENCILMASKSEPARATEPROC)(GLenum face, GLuint mask);
PFNGLSTENCILMASKSEPARATEPROC _gl_loader_glstencilmaskseparate = NULL;
typedef void (APIENTRY *PFNGLSTENCILOPPROC)(GLenum fail, GLenum zfail, GLenum zpass);
PFNGLSTENCILOPPROC _gl_loader_glstencilop = NULL;
typedef void (APIENTRY *PFNGLSTENCILOPSEPARATEPROC)(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
PFNGLSTENCILOPSEPARATEPROC _gl_loader_glstencilopseparate = NULL;
typedef void (APIENTRY *PFNGLTEXBUFFERPROC)(GLenum target, GLenum internalformat, GLuint buffer);
PFNGLTEXBUFFERPROC _gl_loader_gltexbuffer = NULL;
typedef void (APIENTRY *PFNGLTEXBUFFERRANGEPROC)(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
PFNGLTEXBUFFERRANGEPROC _gl_loader_gltexbufferrange = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1DPROC)(GLdouble s);
PFNGLTEXCOORD1DPROC _gl_loader_gltexcoord1d = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1DVPROC)(const GLdouble * v);
PFNGLTEXCOORD1DVPROC _gl_loader_gltexcoord1dv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1FPROC)(GLfloat s);
PFNGLTEXCOORD1FPROC _gl_loader_gltexcoord1f = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1FVPROC)(const GLfloat * v);
PFNGLTEXCOORD1FVPROC _gl_loader_gltexcoord1fv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1IPROC)(GLint s);
PFNGLTEXCOORD1IPROC _gl_loader_gltexcoord1i = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1IVPROC)(const GLint * v);
PFNGLTEXCOORD1IVPROC _gl_loader_gltexcoord1iv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1SPROC)(GLshort s);
PFNGLTEXCOORD1SPROC _gl_loader_gltexcoord1s = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD1SVPROC)(const GLshort * v);
PFNGLTEXCOORD1SVPROC _gl_loader_gltexcoord1sv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2DPROC)(GLdouble s, GLdouble t);
PFNGLTEXCOORD2DPROC _gl_loader_gltexcoord2d = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2DVPROC)(const GLdouble * v);
PFNGLTEXCOORD2DVPROC _gl_loader_gltexcoord2dv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2FPROC)(GLfloat s, GLfloat t);
PFNGLTEXCOORD2FPROC _gl_loader_gltexcoord2f = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2FVPROC)(const GLfloat * v);
PFNGLTEXCOORD2FVPROC _gl_loader_gltexcoord2fv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2IPROC)(GLint s, GLint t);
PFNGLTEXCOORD2IPROC _gl_loader_gltexcoord2i = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2IVPROC)(const GLint * v);
PFNGLTEXCOORD2IVPROC _gl_loader_gltexcoord2iv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2SPROC)(GLshort s, GLshort t);
PFNGLTEXCOORD2SPROC _gl_loader_gltexcoord2s = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD2SVPROC)(const GLshort * v);
PFNGLTEXCOORD2SVPROC _gl_loader_gltexcoord2sv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3DPROC)(GLdouble s, GLdouble t, GLdouble r);
PFNGLTEXCOORD3DPROC _gl_loader_gltexcoord3d = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3DVPROC)(const GLdouble * v);
PFNGLTEXCOORD3DVPROC _gl_loader_gltexcoord3dv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3FPROC)(GLfloat s, GLfloat t, GLfloat r);
PFNGLTEXCOORD3FPROC _gl_loader_gltexcoord3f = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3FVPROC)(const GLfloat * v);
PFNGLTEXCOORD3FVPROC _gl_loader_gltexcoord3fv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3IPROC)(GLint s, GLint t, GLint r);
PFNGLTEXCOORD3IPROC _gl_loader_gltexcoord3i = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3IVPROC)(const GLint * v);
PFNGLTEXCOORD3IVPROC _gl_loader_gltexcoord3iv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3SPROC)(GLshort s, GLshort t, GLshort r);
PFNGLTEXCOORD3SPROC _gl_loader_gltexcoord3s = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD3SVPROC)(const GLshort * v);
PFNGLTEXCOORD3SVPROC _gl_loader_gltexcoord3sv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4DPROC)(GLdouble s, GLdouble t, GLdouble r, GLdouble q);
PFNGLTEXCOORD4DPROC _gl_loader_gltexcoord4d = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4DVPROC)(const GLdouble * v);
PFNGLTEXCOORD4DVPROC _gl_loader_gltexcoord4dv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4FPROC)(GLfloat s, GLfloat t, GLfloat r, GLfloat q);
PFNGLTEXCOORD4FPROC _gl_loader_gltexcoord4f = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4FVPROC)(const GLfloat * v);
PFNGLTEXCOORD4FVPROC _gl_loader_gltexcoord4fv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4IPROC)(GLint s, GLint t, GLint r, GLint q);
PFNGLTEXCOORD4IPROC _gl_loader_gltexcoord4i = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4IVPROC)(const GLint * v);
PFNGLTEXCOORD4IVPROC _gl_loader_gltexcoord4iv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4SPROC)(GLshort s, GLshort t, GLshort r, GLshort q);
PFNGLTEXCOORD4SPROC _gl_loader_gltexcoord4s = NULL;
typedef void (APIENTRY *PFNGLTEXCOORD4SVPROC)(const GLshort * v);
PFNGLTEXCOORD4SVPROC _gl_loader_gltexcoord4sv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP1UIPROC)(GLenum type, GLuint coords);
PFNGLTEXCOORDP1UIPROC _gl_loader_gltexcoordp1ui = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP1UIVPROC)(GLenum type, const GLuint * coords);
PFNGLTEXCOORDP1UIVPROC _gl_loader_gltexcoordp1uiv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP2UIPROC)(GLenum type, GLuint coords);
PFNGLTEXCOORDP2UIPROC _gl_loader_gltexcoordp2ui = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP2UIVPROC)(GLenum type, const GLuint * coords);
PFNGLTEXCOORDP2UIVPROC _gl_loader_gltexcoordp2uiv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP3UIPROC)(GLenum type, GLuint coords);
PFNGLTEXCOORDP3UIPROC _gl_loader_gltexcoordp3ui = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP3UIVPROC)(GLenum type, const GLuint * coords);
PFNGLTEXCOORDP3UIVPROC _gl_loader_gltexcoordp3uiv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP4UIPROC)(GLenum type, GLuint coords);
PFNGLTEXCOORDP4UIPROC _gl_loader_gltexcoordp4ui = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDP4UIVPROC)(GLenum type, const GLuint * coords);
PFNGLTEXCOORDP4UIVPROC _gl_loader_gltexcoordp4uiv = NULL;
typedef void (APIENTRY *PFNGLTEXCOORDPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLTEXCOORDPOINTERPROC _gl_loader_gltexcoordpointer = NULL;
typedef void (APIENTRY *PFNGLTEXENVFPROC)(GLenum target, GLenum pname, GLfloat param);
PFNGLTEXENVFPROC _gl_loader_gltexenvf = NULL;
typedef void (APIENTRY *PFNGLTEXENVFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
PFNGLTEXENVFVPROC _gl_loader_gltexenvfv = NULL;
typedef void (APIENTRY *PFNGLTEXENVIPROC)(GLenum target, GLenum pname, GLint param);
PFNGLTEXENVIPROC _gl_loader_gltexenvi = NULL;
typedef void (APIENTRY *PFNGLTEXENVIVPROC)(GLenum target, GLenum pname, const GLint * params);
PFNGLTEXENVIVPROC _gl_loader_gltexenviv = NULL;
typedef void (APIENTRY *PFNGLTEXGENDPROC)(GLenum coord, GLenum pname, GLdouble param);
PFNGLTEXGENDPROC _gl_loader_gltexgend = NULL;
typedef void (APIENTRY *PFNGLTEXGENDVPROC)(GLenum coord, GLenum pname, const GLdouble * params);
PFNGLTEXGENDVPROC _gl_loader_gltexgendv = NULL;
typedef void (APIENTRY *PFNGLTEXGENFPROC)(GLenum coord, GLenum pname, GLfloat param);
PFNGLTEXGENFPROC _gl_loader_gltexgenf = NULL;
typedef void (APIENTRY *PFNGLTEXGENFVPROC)(GLenum coord, GLenum pname, const GLfloat * params);
PFNGLTEXGENFVPROC _gl_loader_gltexgenfv = NULL;
typedef void (APIENTRY *PFNGLTEXGENIPROC)(GLenum coord, GLenum pname, GLint param);
PFNGLTEXGENIPROC _gl_loader_gltexgeni = NULL;
typedef void (APIENTRY *PFNGLTEXGENIVPROC)(GLenum coord, GLenum pname, const GLint * params);
PFNGLTEXGENIVPROC _gl_loader_gltexgeniv = NULL;
typedef void (APIENTRY *PFNGLTEXIMAGE1DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels);
PFNGLTEXIMAGE1DPROC _gl_loader_glteximage1d = NULL;
typedef void (APIENTRY *PFNGLTEXIMAGE2DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
PFNGLTEXIMAGE2DPROC _gl_loader_glteximage2d = NULL;
typedef void (APIENTRY *PFNGLTEXIMAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
PFNGLTEXIMAGE2DMULTISAMPLEPROC _gl_loader_glteximage2dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXIMAGE3DPROC)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels);
PFNGLTEXIMAGE3DPROC _gl_loader_glteximage3d = NULL;
typedef void (APIENTRY *PFNGLTEXIMAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
PFNGLTEXIMAGE3DMULTISAMPLEPROC _gl_loader_glteximage3dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERIIVPROC)(GLenum target, GLenum pname, const GLint * params);
PFNGLTEXPARAMETERIIVPROC _gl_loader_gltexparameteriiv = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERIUIVPROC)(GLenum target, GLenum pname, const GLuint * params);
PFNGLTEXPARAMETERIUIVPROC _gl_loader_gltexparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERFPROC)(GLenum target, GLenum pname, GLfloat param);
PFNGLTEXPARAMETERFPROC _gl_loader_gltexparameterf = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERFVPROC)(GLenum target, GLenum pname, const GLfloat * params);
PFNGLTEXPARAMETERFVPROC _gl_loader_gltexparameterfv = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERIPROC)(GLenum target, GLenum pname, GLint param);
PFNGLTEXPARAMETERIPROC _gl_loader_gltexparameteri = NULL;
typedef void (APIENTRY *PFNGLTEXPARAMETERIVPROC)(GLenum target, GLenum pname, const GLint * params);
PFNGLTEXPARAMETERIVPROC _gl_loader_gltexparameteriv = NULL;
typedef void (APIENTRY *PFNGLTEXSTORAGE1DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width);
PFNGLTEXSTORAGE1DPROC _gl_loader_gltexstorage1d = NULL;
typedef void (APIENTRY *PFNGLTEXSTORAGE2DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLTEXSTORAGE2DPROC _gl_loader_gltexstorage2d = NULL;
typedef void (APIENTRY *PFNGLTEXSTORAGE2DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
PFNGLTEXSTORAGE2DMULTISAMPLEPROC _gl_loader_gltexstorage2dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXSTORAGE3DPROC)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
PFNGLTEXSTORAGE3DPROC _gl_loader_gltexstorage3d = NULL;
typedef void (APIENTRY *PFNGLTEXSTORAGE3DMULTISAMPLEPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
PFNGLTEXSTORAGE3DMULTISAMPLEPROC _gl_loader_gltexstorage3dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXSUBIMAGE1DPROC)(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
PFNGLTEXSUBIMAGE1DPROC _gl_loader_gltexsubimage1d = NULL;
typedef void (APIENTRY *PFNGLTEXSUBIMAGE2DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
PFNGLTEXSUBIMAGE2DPROC _gl_loader_gltexsubimage2d = NULL;
typedef void (APIENTRY *PFNGLTEXSUBIMAGE3DPROC)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
PFNGLTEXSUBIMAGE3DPROC _gl_loader_gltexsubimage3d = NULL;
typedef void (APIENTRY *PFNGLTEXTUREBARRIERPROC)();
PFNGLTEXTUREBARRIERPROC _gl_loader_gltexturebarrier = NULL;
typedef void (APIENTRY *PFNGLTEXTUREBUFFERPROC)(GLuint texture, GLenum internalformat, GLuint buffer);
PFNGLTEXTUREBUFFERPROC _gl_loader_gltexturebuffer = NULL;
typedef void (APIENTRY *PFNGLTEXTUREBUFFERRANGEPROC)(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
PFNGLTEXTUREBUFFERRANGEPROC _gl_loader_gltexturebufferrange = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERIIVPROC)(GLuint texture, GLenum pname, const GLint * params);
PFNGLTEXTUREPARAMETERIIVPROC _gl_loader_gltextureparameteriiv = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERIUIVPROC)(GLuint texture, GLenum pname, const GLuint * params);
PFNGLTEXTUREPARAMETERIUIVPROC _gl_loader_gltextureparameteriuiv = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERFPROC)(GLuint texture, GLenum pname, GLfloat param);
PFNGLTEXTUREPARAMETERFPROC _gl_loader_gltextureparameterf = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERFVPROC)(GLuint texture, GLenum pname, const GLfloat * param);
PFNGLTEXTUREPARAMETERFVPROC _gl_loader_gltextureparameterfv = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERIPROC)(GLuint texture, GLenum pname, GLint param);
PFNGLTEXTUREPARAMETERIPROC _gl_loader_gltextureparameteri = NULL;
typedef void (APIENTRY *PFNGLTEXTUREPARAMETERIVPROC)(GLuint texture, GLenum pname, const GLint * param);
PFNGLTEXTUREPARAMETERIVPROC _gl_loader_gltextureparameteriv = NULL;
typedef void (APIENTRY *PFNGLTEXTURESTORAGE1DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width);
PFNGLTEXTURESTORAGE1DPROC _gl_loader_gltexturestorage1d = NULL;
typedef void (APIENTRY *PFNGLTEXTURESTORAGE2DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
PFNGLTEXTURESTORAGE2DPROC _gl_loader_gltexturestorage2d = NULL;
typedef void (APIENTRY *PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC _gl_loader_gltexturestorage2dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXTURESTORAGE3DPROC)(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth);
PFNGLTEXTURESTORAGE3DPROC _gl_loader_gltexturestorage3d = NULL;
typedef void (APIENTRY *PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC _gl_loader_gltexturestorage3dmultisample = NULL;
typedef void (APIENTRY *PFNGLTEXTURESUBIMAGE1DPROC)(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels);
PFNGLTEXTURESUBIMAGE1DPROC _gl_loader_gltexturesubimage1d = NULL;
typedef void (APIENTRY *PFNGLTEXTURESUBIMAGE2DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
PFNGLTEXTURESUBIMAGE2DPROC _gl_loader_gltexturesubimage2d = NULL;
typedef void (APIENTRY *PFNGLTEXTURESUBIMAGE3DPROC)(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels);
PFNGLTEXTURESUBIMAGE3DPROC _gl_loader_gltexturesubimage3d = NULL;
typedef void (APIENTRY *PFNGLTEXTUREVIEWPROC)(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers);
PFNGLTEXTUREVIEWPROC _gl_loader_gltextureview = NULL;
typedef void (APIENTRY *PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)(GLuint xfb, GLuint index, GLuint buffer);
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC _gl_loader_gltransformfeedbackbufferbase = NULL;
typedef void (APIENTRY *PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC _gl_loader_gltransformfeedbackbufferrange = NULL;
typedef void (APIENTRY *PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint program, GLsizei count, const GLchar * const * varyings, GLenum bufferMode);
PFNGLTRANSFORMFEEDBACKVARYINGSPROC _gl_loader_gltransformfeedbackvaryings = NULL;
typedef void (APIENTRY *PFNGLTRANSLATEDPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLTRANSLATEDPROC _gl_loader_gltranslated = NULL;
typedef void (APIENTRY *PFNGLTRANSLATEFPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLTRANSLATEFPROC _gl_loader_gltranslatef = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1DPROC)(GLint location, GLdouble x);
PFNGLUNIFORM1DPROC _gl_loader_gluniform1d = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1DVPROC)(GLint location, GLsizei count, const GLdouble * value);
PFNGLUNIFORM1DVPROC _gl_loader_gluniform1dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1FPROC)(GLint location, GLfloat v0);
PFNGLUNIFORM1FPROC _gl_loader_gluniform1f = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1FVPROC)(GLint location, GLsizei count, const GLfloat * value);
PFNGLUNIFORM1FVPROC _gl_loader_gluniform1fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1IPROC)(GLint location, GLint v0);
PFNGLUNIFORM1IPROC _gl_loader_gluniform1i = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1IVPROC)(GLint location, GLsizei count, const GLint * value);
PFNGLUNIFORM1IVPROC _gl_loader_gluniform1iv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1UIPROC)(GLint location, GLuint v0);
PFNGLUNIFORM1UIPROC _gl_loader_gluniform1ui = NULL;
typedef void (APIENTRY *PFNGLUNIFORM1UIVPROC)(GLint location, GLsizei count, const GLuint * value);
PFNGLUNIFORM1UIVPROC _gl_loader_gluniform1uiv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2DPROC)(GLint location, GLdouble x, GLdouble y);
PFNGLUNIFORM2DPROC _gl_loader_gluniform2d = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2DVPROC)(GLint location, GLsizei count, const GLdouble * value);
PFNGLUNIFORM2DVPROC _gl_loader_gluniform2dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2FPROC)(GLint location, GLfloat v0, GLfloat v1);
PFNGLUNIFORM2FPROC _gl_loader_gluniform2f = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2FVPROC)(GLint location, GLsizei count, const GLfloat * value);
PFNGLUNIFORM2FVPROC _gl_loader_gluniform2fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2IPROC)(GLint location, GLint v0, GLint v1);
PFNGLUNIFORM2IPROC _gl_loader_gluniform2i = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2IVPROC)(GLint location, GLsizei count, const GLint * value);
PFNGLUNIFORM2IVPROC _gl_loader_gluniform2iv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2UIPROC)(GLint location, GLuint v0, GLuint v1);
PFNGLUNIFORM2UIPROC _gl_loader_gluniform2ui = NULL;
typedef void (APIENTRY *PFNGLUNIFORM2UIVPROC)(GLint location, GLsizei count, const GLuint * value);
PFNGLUNIFORM2UIVPROC _gl_loader_gluniform2uiv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z);
PFNGLUNIFORM3DPROC _gl_loader_gluniform3d = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3DVPROC)(GLint location, GLsizei count, const GLdouble * value);
PFNGLUNIFORM3DVPROC _gl_loader_gluniform3dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
PFNGLUNIFORM3FPROC _gl_loader_gluniform3f = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3FVPROC)(GLint location, GLsizei count, const GLfloat * value);
PFNGLUNIFORM3FVPROC _gl_loader_gluniform3fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3IPROC)(GLint location, GLint v0, GLint v1, GLint v2);
PFNGLUNIFORM3IPROC _gl_loader_gluniform3i = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3IVPROC)(GLint location, GLsizei count, const GLint * value);
PFNGLUNIFORM3IVPROC _gl_loader_gluniform3iv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2);
PFNGLUNIFORM3UIPROC _gl_loader_gluniform3ui = NULL;
typedef void (APIENTRY *PFNGLUNIFORM3UIVPROC)(GLint location, GLsizei count, const GLuint * value);
PFNGLUNIFORM3UIVPROC _gl_loader_gluniform3uiv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4DPROC)(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLUNIFORM4DPROC _gl_loader_gluniform4d = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4DVPROC)(GLint location, GLsizei count, const GLdouble * value);
PFNGLUNIFORM4DVPROC _gl_loader_gluniform4dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4FPROC)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
PFNGLUNIFORM4FPROC _gl_loader_gluniform4f = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4FVPROC)(GLint location, GLsizei count, const GLfloat * value);
PFNGLUNIFORM4FVPROC _gl_loader_gluniform4fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4IPROC)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
PFNGLUNIFORM4IPROC _gl_loader_gluniform4i = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4IVPROC)(GLint location, GLsizei count, const GLint * value);
PFNGLUNIFORM4IVPROC _gl_loader_gluniform4iv = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4UIPROC)(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3);
PFNGLUNIFORM4UIPROC _gl_loader_gluniform4ui = NULL;
typedef void (APIENTRY *PFNGLUNIFORM4UIVPROC)(GLint location, GLsizei count, const GLuint * value);
PFNGLUNIFORM4UIVPROC _gl_loader_gluniform4uiv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMBLOCKBINDINGPROC)(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding);
PFNGLUNIFORMBLOCKBINDINGPROC _gl_loader_gluniformblockbinding = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX2DVPROC _gl_loader_gluniformmatrix2dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX2FVPROC _gl_loader_gluniformmatrix2fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX2X3DVPROC _gl_loader_gluniformmatrix2x3dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX2X3FVPROC _gl_loader_gluniformmatrix2x3fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX2X4DVPROC _gl_loader_gluniformmatrix2x4dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX2X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX2X4FVPROC _gl_loader_gluniformmatrix2x4fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX3DVPROC _gl_loader_gluniformmatrix3dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX3FVPROC _gl_loader_gluniformmatrix3fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX3X2DVPROC _gl_loader_gluniformmatrix3x2dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX3X2FVPROC _gl_loader_gluniformmatrix3x2fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3X4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX3X4DVPROC _gl_loader_gluniformmatrix3x4dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX3X4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX3X4FVPROC _gl_loader_gluniformmatrix3x4fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX4DVPROC _gl_loader_gluniformmatrix4dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX4FVPROC _gl_loader_gluniformmatrix4fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4X2DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX4X2DVPROC _gl_loader_gluniformmatrix4x2dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4X2FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX4X2FVPROC _gl_loader_gluniformmatrix4x2fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4X3DVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value);
PFNGLUNIFORMMATRIX4X3DVPROC _gl_loader_gluniformmatrix4x3dv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMMATRIX4X3FVPROC)(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
PFNGLUNIFORMMATRIX4X3FVPROC _gl_loader_gluniformmatrix4x3fv = NULL;
typedef void (APIENTRY *PFNGLUNIFORMSUBROUTINESUIVPROC)(GLenum shadertype, GLsizei count, const GLuint * indices);
PFNGLUNIFORMSUBROUTINESUIVPROC _gl_loader_gluniformsubroutinesuiv = NULL;
typedef GLboolean (APIENTRY *PFNGLUNMAPBUFFERPROC)(GLenum target);
PFNGLUNMAPBUFFERPROC _gl_loader_glunmapbuffer = NULL;
typedef GLboolean (APIENTRY *PFNGLUNMAPNAMEDBUFFERPROC)(GLuint buffer);
PFNGLUNMAPNAMEDBUFFERPROC _gl_loader_glunmapnamedbuffer = NULL;
typedef void (APIENTRY *PFNGLUSEPROGRAMPROC)(GLuint program);
PFNGLUSEPROGRAMPROC _gl_loader_gluseprogram = NULL;
typedef void (APIENTRY *PFNGLUSEPROGRAMSTAGESPROC)(GLuint pipeline, GLbitfield stages, GLuint program);
PFNGLUSEPROGRAMSTAGESPROC _gl_loader_gluseprogramstages = NULL;
typedef void (APIENTRY *PFNGLVALIDATEPROGRAMPROC)(GLuint program);
PFNGLVALIDATEPROGRAMPROC _gl_loader_glvalidateprogram = NULL;
typedef void (APIENTRY *PFNGLVALIDATEPROGRAMPIPELINEPROC)(GLuint pipeline);
PFNGLVALIDATEPROGRAMPIPELINEPROC _gl_loader_glvalidateprogrampipeline = NULL;
typedef void (APIENTRY *PFNGLVERTEX2DPROC)(GLdouble x, GLdouble y);
PFNGLVERTEX2DPROC _gl_loader_glvertex2d = NULL;
typedef void (APIENTRY *PFNGLVERTEX2DVPROC)(const GLdouble * v);
PFNGLVERTEX2DVPROC _gl_loader_glvertex2dv = NULL;
typedef void (APIENTRY *PFNGLVERTEX2FPROC)(GLfloat x, GLfloat y);
PFNGLVERTEX2FPROC _gl_loader_glvertex2f = NULL;
typedef void (APIENTRY *PFNGLVERTEX2FVPROC)(const GLfloat * v);
PFNGLVERTEX2FVPROC _gl_loader_glvertex2fv = NULL;
typedef void (APIENTRY *PFNGLVERTEX2IPROC)(GLint x, GLint y);
PFNGLVERTEX2IPROC _gl_loader_glvertex2i = NULL;
typedef void (APIENTRY *PFNGLVERTEX2IVPROC)(const GLint * v);
PFNGLVERTEX2IVPROC _gl_loader_glvertex2iv = NULL;
typedef void (APIENTRY *PFNGLVERTEX2SPROC)(GLshort x, GLshort y);
PFNGLVERTEX2SPROC _gl_loader_glvertex2s = NULL;
typedef void (APIENTRY *PFNGLVERTEX2SVPROC)(const GLshort * v);
PFNGLVERTEX2SVPROC _gl_loader_glvertex2sv = NULL;
typedef void (APIENTRY *PFNGLVERTEX3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLVERTEX3DPROC _gl_loader_glvertex3d = NULL;
typedef void (APIENTRY *PFNGLVERTEX3DVPROC)(const GLdouble * v);
PFNGLVERTEX3DVPROC _gl_loader_glvertex3dv = NULL;
typedef void (APIENTRY *PFNGLVERTEX3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLVERTEX3FPROC _gl_loader_glvertex3f = NULL;
typedef void (APIENTRY *PFNGLVERTEX3FVPROC)(const GLfloat * v);
PFNGLVERTEX3FVPROC _gl_loader_glvertex3fv = NULL;
typedef void (APIENTRY *PFNGLVERTEX3IPROC)(GLint x, GLint y, GLint z);
PFNGLVERTEX3IPROC _gl_loader_glvertex3i = NULL;
typedef void (APIENTRY *PFNGLVERTEX3IVPROC)(const GLint * v);
PFNGLVERTEX3IVPROC _gl_loader_glvertex3iv = NULL;
typedef void (APIENTRY *PFNGLVERTEX3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLVERTEX3SPROC _gl_loader_glvertex3s = NULL;
typedef void (APIENTRY *PFNGLVERTEX3SVPROC)(const GLshort * v);
PFNGLVERTEX3SVPROC _gl_loader_glvertex3sv = NULL;
typedef void (APIENTRY *PFNGLVERTEX4DPROC)(GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLVERTEX4DPROC _gl_loader_glvertex4d = NULL;
typedef void (APIENTRY *PFNGLVERTEX4DVPROC)(const GLdouble * v);
PFNGLVERTEX4DVPROC _gl_loader_glvertex4dv = NULL;
typedef void (APIENTRY *PFNGLVERTEX4FPROC)(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLVERTEX4FPROC _gl_loader_glvertex4f = NULL;
typedef void (APIENTRY *PFNGLVERTEX4FVPROC)(const GLfloat * v);
PFNGLVERTEX4FVPROC _gl_loader_glvertex4fv = NULL;
typedef void (APIENTRY *PFNGLVERTEX4IPROC)(GLint x, GLint y, GLint z, GLint w);
PFNGLVERTEX4IPROC _gl_loader_glvertex4i = NULL;
typedef void (APIENTRY *PFNGLVERTEX4IVPROC)(const GLint * v);
PFNGLVERTEX4IVPROC _gl_loader_glvertex4iv = NULL;
typedef void (APIENTRY *PFNGLVERTEX4SPROC)(GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLVERTEX4SPROC _gl_loader_glvertex4s = NULL;
typedef void (APIENTRY *PFNGLVERTEX4SVPROC)(const GLshort * v);
PFNGLVERTEX4SVPROC _gl_loader_glvertex4sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYATTRIBBINDINGPROC)(GLuint vaobj, GLuint attribindex, GLuint bindingindex);
PFNGLVERTEXARRAYATTRIBBINDINGPROC _gl_loader_glvertexarrayattribbinding = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYATTRIBFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
PFNGLVERTEXARRAYATTRIBFORMATPROC _gl_loader_glvertexarrayattribformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYATTRIBIFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
PFNGLVERTEXARRAYATTRIBIFORMATPROC _gl_loader_glvertexarrayattribiformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYATTRIBLFORMATPROC)(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
PFNGLVERTEXARRAYATTRIBLFORMATPROC _gl_loader_glvertexarrayattriblformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYBINDINGDIVISORPROC)(GLuint vaobj, GLuint bindingindex, GLuint divisor);
PFNGLVERTEXARRAYBINDINGDIVISORPROC _gl_loader_glvertexarraybindingdivisor = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYELEMENTBUFFERPROC)(GLuint vaobj, GLuint buffer);
PFNGLVERTEXARRAYELEMENTBUFFERPROC _gl_loader_glvertexarrayelementbuffer = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYVERTEXBUFFERPROC)(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride);
PFNGLVERTEXARRAYVERTEXBUFFERPROC _gl_loader_glvertexarrayvertexbuffer = NULL;
typedef void (APIENTRY *PFNGLVERTEXARRAYVERTEXBUFFERSPROC)(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides);
PFNGLVERTEXARRAYVERTEXBUFFERSPROC _gl_loader_glvertexarrayvertexbuffers = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1DPROC)(GLuint index, GLdouble x);
PFNGLVERTEXATTRIB1DPROC _gl_loader_glvertexattrib1d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIB1DVPROC _gl_loader_glvertexattrib1dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1FPROC)(GLuint index, GLfloat x);
PFNGLVERTEXATTRIB1FPROC _gl_loader_glvertexattrib1f = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1FVPROC)(GLuint index, const GLfloat * v);
PFNGLVERTEXATTRIB1FVPROC _gl_loader_glvertexattrib1fv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1SPROC)(GLuint index, GLshort x);
PFNGLVERTEXATTRIB1SPROC _gl_loader_glvertexattrib1s = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB1SVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIB1SVPROC _gl_loader_glvertexattrib1sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2DPROC)(GLuint index, GLdouble x, GLdouble y);
PFNGLVERTEXATTRIB2DPROC _gl_loader_glvertexattrib2d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIB2DVPROC _gl_loader_glvertexattrib2dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2FPROC)(GLuint index, GLfloat x, GLfloat y);
PFNGLVERTEXATTRIB2FPROC _gl_loader_glvertexattrib2f = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2FVPROC)(GLuint index, const GLfloat * v);
PFNGLVERTEXATTRIB2FVPROC _gl_loader_glvertexattrib2fv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2SPROC)(GLuint index, GLshort x, GLshort y);
PFNGLVERTEXATTRIB2SPROC _gl_loader_glvertexattrib2s = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB2SVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIB2SVPROC _gl_loader_glvertexattrib2sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
PFNGLVERTEXATTRIB3DPROC _gl_loader_glvertexattrib3d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIB3DVPROC _gl_loader_glvertexattrib3dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z);
PFNGLVERTEXATTRIB3FPROC _gl_loader_glvertexattrib3f = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3FVPROC)(GLuint index, const GLfloat * v);
PFNGLVERTEXATTRIB3FVPROC _gl_loader_glvertexattrib3fv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3SPROC)(GLuint index, GLshort x, GLshort y, GLshort z);
PFNGLVERTEXATTRIB3SPROC _gl_loader_glvertexattrib3s = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB3SVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIB3SVPROC _gl_loader_glvertexattrib3sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NBVPROC)(GLuint index, const GLbyte * v);
PFNGLVERTEXATTRIB4NBVPROC _gl_loader_glvertexattrib4nbv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NIVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIB4NIVPROC _gl_loader_glvertexattrib4niv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NSVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIB4NSVPROC _gl_loader_glvertexattrib4nsv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NUBPROC)(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w);
PFNGLVERTEXATTRIB4NUBPROC _gl_loader_glvertexattrib4nub = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NUBVPROC)(GLuint index, const GLubyte * v);
PFNGLVERTEXATTRIB4NUBVPROC _gl_loader_glvertexattrib4nubv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NUIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIB4NUIVPROC _gl_loader_glvertexattrib4nuiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4NUSVPROC)(GLuint index, const GLushort * v);
PFNGLVERTEXATTRIB4NUSVPROC _gl_loader_glvertexattrib4nusv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4BVPROC)(GLuint index, const GLbyte * v);
PFNGLVERTEXATTRIB4BVPROC _gl_loader_glvertexattrib4bv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLVERTEXATTRIB4DPROC _gl_loader_glvertexattrib4d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIB4DVPROC _gl_loader_glvertexattrib4dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4FPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
PFNGLVERTEXATTRIB4FPROC _gl_loader_glvertexattrib4f = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4FVPROC)(GLuint index, const GLfloat * v);
PFNGLVERTEXATTRIB4FVPROC _gl_loader_glvertexattrib4fv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4IVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIB4IVPROC _gl_loader_glvertexattrib4iv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4SPROC)(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w);
PFNGLVERTEXATTRIB4SPROC _gl_loader_glvertexattrib4s = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4SVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIB4SVPROC _gl_loader_glvertexattrib4sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4UBVPROC)(GLuint index, const GLubyte * v);
PFNGLVERTEXATTRIB4UBVPROC _gl_loader_glvertexattrib4ubv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4UIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIB4UIVPROC _gl_loader_glvertexattrib4uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIB4USVPROC)(GLuint index, const GLushort * v);
PFNGLVERTEXATTRIB4USVPROC _gl_loader_glvertexattrib4usv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBBINDINGPROC)(GLuint attribindex, GLuint bindingindex);
PFNGLVERTEXATTRIBBINDINGPROC _gl_loader_glvertexattribbinding = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBDIVISORPROC)(GLuint index, GLuint divisor);
PFNGLVERTEXATTRIBDIVISORPROC _gl_loader_glvertexattribdivisor = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset);
PFNGLVERTEXATTRIBFORMATPROC _gl_loader_glvertexattribformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI1IPROC)(GLuint index, GLint x);
PFNGLVERTEXATTRIBI1IPROC _gl_loader_glvertexattribi1i = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI1IVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIBI1IVPROC _gl_loader_glvertexattribi1iv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI1UIPROC)(GLuint index, GLuint x);
PFNGLVERTEXATTRIBI1UIPROC _gl_loader_glvertexattribi1ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI1UIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIBI1UIVPROC _gl_loader_glvertexattribi1uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI2IPROC)(GLuint index, GLint x, GLint y);
PFNGLVERTEXATTRIBI2IPROC _gl_loader_glvertexattribi2i = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI2IVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIBI2IVPROC _gl_loader_glvertexattribi2iv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI2UIPROC)(GLuint index, GLuint x, GLuint y);
PFNGLVERTEXATTRIBI2UIPROC _gl_loader_glvertexattribi2ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI2UIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIBI2UIVPROC _gl_loader_glvertexattribi2uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI3IPROC)(GLuint index, GLint x, GLint y, GLint z);
PFNGLVERTEXATTRIBI3IPROC _gl_loader_glvertexattribi3i = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI3IVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIBI3IVPROC _gl_loader_glvertexattribi3iv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI3UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z);
PFNGLVERTEXATTRIBI3UIPROC _gl_loader_glvertexattribi3ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI3UIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIBI3UIVPROC _gl_loader_glvertexattribi3uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4BVPROC)(GLuint index, const GLbyte * v);
PFNGLVERTEXATTRIBI4BVPROC _gl_loader_glvertexattribi4bv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4IPROC)(GLuint index, GLint x, GLint y, GLint z, GLint w);
PFNGLVERTEXATTRIBI4IPROC _gl_loader_glvertexattribi4i = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4IVPROC)(GLuint index, const GLint * v);
PFNGLVERTEXATTRIBI4IVPROC _gl_loader_glvertexattribi4iv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4SVPROC)(GLuint index, const GLshort * v);
PFNGLVERTEXATTRIBI4SVPROC _gl_loader_glvertexattribi4sv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4UBVPROC)(GLuint index, const GLubyte * v);
PFNGLVERTEXATTRIBI4UBVPROC _gl_loader_glvertexattribi4ubv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4UIPROC)(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w);
PFNGLVERTEXATTRIBI4UIPROC _gl_loader_glvertexattribi4ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4UIVPROC)(GLuint index, const GLuint * v);
PFNGLVERTEXATTRIBI4UIVPROC _gl_loader_glvertexattribi4uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBI4USVPROC)(GLuint index, const GLushort * v);
PFNGLVERTEXATTRIBI4USVPROC _gl_loader_glvertexattribi4usv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBIFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
PFNGLVERTEXATTRIBIFORMATPROC _gl_loader_glvertexattribiformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLVERTEXATTRIBIPOINTERPROC _gl_loader_glvertexattribipointer = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL1DPROC)(GLuint index, GLdouble x);
PFNGLVERTEXATTRIBL1DPROC _gl_loader_glvertexattribl1d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL1DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIBL1DVPROC _gl_loader_glvertexattribl1dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL2DPROC)(GLuint index, GLdouble x, GLdouble y);
PFNGLVERTEXATTRIBL2DPROC _gl_loader_glvertexattribl2d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL2DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIBL2DVPROC _gl_loader_glvertexattribl2dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL3DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z);
PFNGLVERTEXATTRIBL3DPROC _gl_loader_glvertexattribl3d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL3DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIBL3DVPROC _gl_loader_glvertexattribl3dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL4DPROC)(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w);
PFNGLVERTEXATTRIBL4DPROC _gl_loader_glvertexattribl4d = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBL4DVPROC)(GLuint index, const GLdouble * v);
PFNGLVERTEXATTRIBL4DVPROC _gl_loader_glvertexattribl4dv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBLFORMATPROC)(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset);
PFNGLVERTEXATTRIBLFORMATPROC _gl_loader_glvertexattriblformat = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBLPOINTERPROC)(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLVERTEXATTRIBLPOINTERPROC _gl_loader_glvertexattriblpointer = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP1UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
PFNGLVERTEXATTRIBP1UIPROC _gl_loader_glvertexattribp1ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP1UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
PFNGLVERTEXATTRIBP1UIVPROC _gl_loader_glvertexattribp1uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP2UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
PFNGLVERTEXATTRIBP2UIPROC _gl_loader_glvertexattribp2ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP2UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
PFNGLVERTEXATTRIBP2UIVPROC _gl_loader_glvertexattribp2uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP3UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
PFNGLVERTEXATTRIBP3UIPROC _gl_loader_glvertexattribp3ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP3UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
PFNGLVERTEXATTRIBP3UIVPROC _gl_loader_glvertexattribp3uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP4UIPROC)(GLuint index, GLenum type, GLboolean normalized, GLuint value);
PFNGLVERTEXATTRIBP4UIPROC _gl_loader_glvertexattribp4ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBP4UIVPROC)(GLuint index, GLenum type, GLboolean normalized, const GLuint * value);
PFNGLVERTEXATTRIBP4UIVPROC _gl_loader_glvertexattribp4uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
PFNGLVERTEXATTRIBPOINTERPROC _gl_loader_glvertexattribpointer = NULL;
typedef void (APIENTRY *PFNGLVERTEXBINDINGDIVISORPROC)(GLuint bindingindex, GLuint divisor);
PFNGLVERTEXBINDINGDIVISORPROC _gl_loader_glvertexbindingdivisor = NULL;
typedef void (APIENTRY *PFNGLVERTEXP2UIPROC)(GLenum type, GLuint value);
PFNGLVERTEXP2UIPROC _gl_loader_glvertexp2ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXP2UIVPROC)(GLenum type, const GLuint * value);
PFNGLVERTEXP2UIVPROC _gl_loader_glvertexp2uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXP3UIPROC)(GLenum type, GLuint value);
PFNGLVERTEXP3UIPROC _gl_loader_glvertexp3ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXP3UIVPROC)(GLenum type, const GLuint * value);
PFNGLVERTEXP3UIVPROC _gl_loader_glvertexp3uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXP4UIPROC)(GLenum type, GLuint value);
PFNGLVERTEXP4UIPROC _gl_loader_glvertexp4ui = NULL;
typedef void (APIENTRY *PFNGLVERTEXP4UIVPROC)(GLenum type, const GLuint * value);
PFNGLVERTEXP4UIVPROC _gl_loader_glvertexp4uiv = NULL;
typedef void (APIENTRY *PFNGLVERTEXPOINTERPROC)(GLint size, GLenum type, GLsizei stride, const void * pointer);
PFNGLVERTEXPOINTERPROC _gl_loader_glvertexpointer = NULL;
typedef void (APIENTRY *PFNGLVIEWPORTPROC)(GLint x, GLint y, GLsizei width, GLsizei height);
PFNGLVIEWPORTPROC _gl_loader_glviewport = NULL;
typedef void (APIENTRY *PFNGLVIEWPORTARRAYVPROC)(GLuint first, GLsizei count, const GLfloat * v);
PFNGLVIEWPORTARRAYVPROC _gl_loader_glviewportarrayv = NULL;
typedef void (APIENTRY *PFNGLVIEWPORTINDEXEDFPROC)(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h);
PFNGLVIEWPORTINDEXEDFPROC _gl_loader_glviewportindexedf = NULL;
typedef void (APIENTRY *PFNGLVIEWPORTINDEXEDFVPROC)(GLuint index, const GLfloat * v);
PFNGLVIEWPORTINDEXEDFVPROC _gl_loader_glviewportindexedfv = NULL;
typedef void (APIENTRY *PFNGLWAITSYNCPROC)(GLsync sync, GLbitfield flags, GLuint64 timeout);
PFNGLWAITSYNCPROC _gl_loader_glwaitsync = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2DPROC)(GLdouble x, GLdouble y);
PFNGLWINDOWPOS2DPROC _gl_loader_glwindowpos2d = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2DVPROC)(const GLdouble * v);
PFNGLWINDOWPOS2DVPROC _gl_loader_glwindowpos2dv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2FPROC)(GLfloat x, GLfloat y);
PFNGLWINDOWPOS2FPROC _gl_loader_glwindowpos2f = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2FVPROC)(const GLfloat * v);
PFNGLWINDOWPOS2FVPROC _gl_loader_glwindowpos2fv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2IPROC)(GLint x, GLint y);
PFNGLWINDOWPOS2IPROC _gl_loader_glwindowpos2i = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2IVPROC)(const GLint * v);
PFNGLWINDOWPOS2IVPROC _gl_loader_glwindowpos2iv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2SPROC)(GLshort x, GLshort y);
PFNGLWINDOWPOS2SPROC _gl_loader_glwindowpos2s = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS2SVPROC)(const GLshort * v);
PFNGLWINDOWPOS2SVPROC _gl_loader_glwindowpos2sv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3DPROC)(GLdouble x, GLdouble y, GLdouble z);
PFNGLWINDOWPOS3DPROC _gl_loader_glwindowpos3d = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3DVPROC)(const GLdouble * v);
PFNGLWINDOWPOS3DVPROC _gl_loader_glwindowpos3dv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3FPROC)(GLfloat x, GLfloat y, GLfloat z);
PFNGLWINDOWPOS3FPROC _gl_loader_glwindowpos3f = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3FVPROC)(const GLfloat * v);
PFNGLWINDOWPOS3FVPROC _gl_loader_glwindowpos3fv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3IPROC)(GLint x, GLint y, GLint z);
PFNGLWINDOWPOS3IPROC _gl_loader_glwindowpos3i = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3IVPROC)(const GLint * v);
PFNGLWINDOWPOS3IVPROC _gl_loader_glwindowpos3iv = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3SPROC)(GLshort x, GLshort y, GLshort z);
PFNGLWINDOWPOS3SPROC _gl_loader_glwindowpos3s = NULL;
typedef void (APIENTRY *PFNGLWINDOWPOS3SVPROC)(const GLshort * v);
PFNGLWINDOWPOS3SVPROC _gl_loader_glwindowpos3sv = NULL;


inline void glAccum(GLenum op, GLfloat value){return _gl_loader_glaccum(op, value);}
inline void glActiveShaderProgram(GLuint pipeline, GLuint program){return _gl_loader_glactiveshaderprogram(pipeline, program);}
inline void glActiveTexture(GLenum texture){return _gl_loader_glactivetexture(texture);}
inline void glAlphaFunc(GLenum func, GLfloat ref){return _gl_loader_glalphafunc(func, ref);}
inline GLboolean glAreTexturesResident(GLsizei n, const GLuint * textures, GLboolean * residences){return _gl_loader_glaretexturesresident(n, textures, residences);}
inline void glArrayElement(GLint i){return _gl_loader_glarrayelement(i);}
inline void glAttachShader(GLuint program, GLuint shader){return _gl_loader_glattachshader(program, shader);}
inline void glBegin(GLenum mode){return _gl_loader_glbegin(mode);}
inline void glBeginConditionalRender(GLuint id, GLenum mode){return _gl_loader_glbeginconditionalrender(id, mode);}
inline void glBeginQuery(GLenum target, GLuint id){return _gl_loader_glbeginquery(target, id);}
inline void glBeginQueryIndexed(GLenum target, GLuint index, GLuint id){return _gl_loader_glbeginqueryindexed(target, index, id);}
inline void glBeginTransformFeedback(GLenum primitiveMode){return _gl_loader_glbegintransformfeedback(primitiveMode);}
inline void glBindAttribLocation(GLuint program, GLuint index, const GLchar * name){return _gl_loader_glbindattriblocation(program, index, name);}
inline void glBindBuffer(GLenum target, GLuint buffer){return _gl_loader_glbindbuffer(target, buffer);}
inline void glBindBufferBase(GLenum target, GLuint index, GLuint buffer){return _gl_loader_glbindbufferbase(target, index, buffer);}
inline void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){return _gl_loader_glbindbufferrange(target, index, buffer, offset, size);}
inline void glBindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers){return _gl_loader_glbindbuffersbase(target, first, count, buffers);}
inline void glBindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes){return _gl_loader_glbindbuffersrange(target, first, count, buffers, offsets, sizes);}
inline void glBindFragDataLocation(GLuint program, GLuint color, const GLchar * name){return _gl_loader_glbindfragdatalocation(program, color, name);}
inline void glBindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name){return _gl_loader_glbindfragdatalocationindexed(program, colorNumber, index, name);}
inline void glBindFramebuffer(GLenum target, GLuint framebuffer){return _gl_loader_glbindframebuffer(target, framebuffer);}
inline void glBindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format){return _gl_loader_glbindimagetexture(unit, texture, level, layered, layer, access, format);}
inline void glBindImageTextures(GLuint first, GLsizei count, const GLuint * textures){return _gl_loader_glbindimagetextures(first, count, textures);}
inline void glBindProgramPipeline(GLuint pipeline){return _gl_loader_glbindprogrampipeline(pipeline);}
inline void glBindRenderbuffer(GLenum target, GLuint renderbuffer){return _gl_loader_glbindrenderbuffer(target, renderbuffer);}
inline void glBindSampler(GLuint unit, GLuint sampler){return _gl_loader_glbindsampler(unit, sampler);}
inline void glBindSamplers(GLuint first, GLsizei count, const GLuint * samplers){return _gl_loader_glbindsamplers(first, count, samplers);}
inline void glBindTexture(GLenum target, GLuint texture){return _gl_loader_glbindtexture(target, texture);}
inline void glBindTextureUnit(GLuint unit, GLuint texture){return _gl_loader_glbindtextureunit(unit, texture);}
inline void glBindTextures(GLuint first, GLsizei count, const GLuint * textures){return _gl_loader_glbindtextures(first, count, textures);}
inline void glBindTransformFeedback(GLenum target, GLuint id){return _gl_loader_glbindtransformfeedback(target, id);}
inline void glBindVertexArray(GLuint array){return _gl_loader_glbindvertexarray(array);}
inline void glBindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){return _gl_loader_glbindvertexbuffer(bindingindex, buffer, offset, stride);}
inline void glBindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides){return _gl_loader_glbindvertexbuffers(first, count, buffers, offsets, strides);}
inline void glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte * bitmap){return _gl_loader_glbitmap(width, height, xorig, yorig, xmove, ymove, bitmap);}
inline void glBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){return _gl_loader_glblendcolor(red, green, blue, alpha);}
inline void glBlendEquation(GLenum mode){return _gl_loader_glblendequation(mode);}
inline void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha){return _gl_loader_glblendequationseparate(modeRGB, modeAlpha);}
inline void glBlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha){return _gl_loader_glblendequationseparatei(buf, modeRGB, modeAlpha);}
inline void glBlendEquationi(GLuint buf, GLenum mode){return _gl_loader_glblendequationi(buf, mode);}
inline void glBlendFunc(GLenum sfactor, GLenum dfactor){return _gl_loader_glblendfunc(sfactor, dfactor);}
inline void glBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha){return _gl_loader_glblendfuncseparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);}
inline void glBlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha){return _gl_loader_glblendfuncseparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);}
inline void glBlendFunci(GLuint buf, GLenum src, GLenum dst){return _gl_loader_glblendfunci(buf, src, dst);}
inline void glBlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){return _gl_loader_glblitframebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
inline void glBlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter){return _gl_loader_glblitnamedframebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);}
inline void glBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage){return _gl_loader_glbufferdata(target, size, data, usage);}
inline void glBufferStorage(GLenum target, GLsizeiptr size, const void * data, GLbitfield flags){return _gl_loader_glbufferstorage(target, size, data, flags);}
inline void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data){return _gl_loader_glbuffersubdata(target, offset, size, data);}
inline void glCallList(GLuint list){return _gl_loader_glcalllist(list);}
inline void glCallLists(GLsizei n, GLenum type, const void * lists){return _gl_loader_glcalllists(n, type, lists);}
inline GLenum glCheckFramebufferStatus(GLenum target){return _gl_loader_glcheckframebufferstatus(target);}
inline GLenum glCheckNamedFramebufferStatus(GLuint framebuffer, GLenum target){return _gl_loader_glchecknamedframebufferstatus(framebuffer, target);}
inline void glClampColor(GLenum target, GLenum clamp){return _gl_loader_glclampcolor(target, clamp);}
inline void glClear(GLbitfield mask){return _gl_loader_glclear(mask);}
inline void glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){return _gl_loader_glclearaccum(red, green, blue, alpha);}
inline void glClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const void * data){return _gl_loader_glclearbufferdata(target, internalformat, format, type, data);}
inline void glClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data){return _gl_loader_glclearbuffersubdata(target, internalformat, offset, size, format, type, data);}
inline void glClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){return _gl_loader_glclearbufferfi(buffer, drawbuffer, depth, stencil);}
inline void glClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value){return _gl_loader_glclearbufferfv(buffer, drawbuffer, value);}
inline void glClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value){return _gl_loader_glclearbufferiv(buffer, drawbuffer, value);}
inline void glClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value){return _gl_loader_glclearbufferuiv(buffer, drawbuffer, value);}
inline void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){return _gl_loader_glclearcolor(red, green, blue, alpha);}
inline void glClearDepth(GLdouble depth){return _gl_loader_glcleardepth(depth);}
inline void glClearDepthf(GLfloat d){return _gl_loader_glcleardepthf(d);}
inline void glClearIndex(GLfloat c){return _gl_loader_glclearindex(c);}
inline void glClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const void * data){return _gl_loader_glclearnamedbufferdata(buffer, internalformat, format, type, data);}
inline void glClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const void * data){return _gl_loader_glclearnamedbuffersubdata(buffer, internalformat, offset, size, format, type, data);}
inline void glClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil){return _gl_loader_glclearnamedframebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);}
inline void glClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value){return _gl_loader_glclearnamedframebufferfv(framebuffer, buffer, drawbuffer, value);}
inline void glClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value){return _gl_loader_glclearnamedframebufferiv(framebuffer, buffer, drawbuffer, value);}
inline void glClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value){return _gl_loader_glclearnamedframebufferuiv(framebuffer, buffer, drawbuffer, value);}
inline void glClearStencil(GLint s){return _gl_loader_glclearstencil(s);}
inline void glClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const void * data){return _gl_loader_glclearteximage(texture, level, format, type, data);}
inline void glClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * data){return _gl_loader_glcleartexsubimage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);}
inline void glClientActiveTexture(GLenum texture){return _gl_loader_glclientactivetexture(texture);}
inline GLenum glClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){return _gl_loader_glclientwaitsync(sync, flags, timeout);}
inline void glClipControl(GLenum origin, GLenum depth){return _gl_loader_glclipcontrol(origin, depth);}
inline void glClipPlane(GLenum plane, const GLdouble * equation){return _gl_loader_glclipplane(plane, equation);}
inline void glColor3b(GLbyte red, GLbyte green, GLbyte blue){return _gl_loader_glcolor3b(red, green, blue);}
inline void glColor3bv(const GLbyte * v){return _gl_loader_glcolor3bv(v);}
inline void glColor3d(GLdouble red, GLdouble green, GLdouble blue){return _gl_loader_glcolor3d(red, green, blue);}
inline void glColor3dv(const GLdouble * v){return _gl_loader_glcolor3dv(v);}
inline void glColor3f(GLfloat red, GLfloat green, GLfloat blue){return _gl_loader_glcolor3f(red, green, blue);}
inline void glColor3fv(const GLfloat * v){return _gl_loader_glcolor3fv(v);}
inline void glColor3i(GLint red, GLint green, GLint blue){return _gl_loader_glcolor3i(red, green, blue);}
inline void glColor3iv(const GLint * v){return _gl_loader_glcolor3iv(v);}
inline void glColor3s(GLshort red, GLshort green, GLshort blue){return _gl_loader_glcolor3s(red, green, blue);}
inline void glColor3sv(const GLshort * v){return _gl_loader_glcolor3sv(v);}
inline void glColor3ub(GLubyte red, GLubyte green, GLubyte blue){return _gl_loader_glcolor3ub(red, green, blue);}
inline void glColor3ubv(const GLubyte * v){return _gl_loader_glcolor3ubv(v);}
inline void glColor3ui(GLuint red, GLuint green, GLuint blue){return _gl_loader_glcolor3ui(red, green, blue);}
inline void glColor3uiv(const GLuint * v){return _gl_loader_glcolor3uiv(v);}
inline void glColor3us(GLushort red, GLushort green, GLushort blue){return _gl_loader_glcolor3us(red, green, blue);}
inline void glColor3usv(const GLushort * v){return _gl_loader_glcolor3usv(v);}
inline void glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha){return _gl_loader_glcolor4b(red, green, blue, alpha);}
inline void glColor4bv(const GLbyte * v){return _gl_loader_glcolor4bv(v);}
inline void glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha){return _gl_loader_glcolor4d(red, green, blue, alpha);}
inline void glColor4dv(const GLdouble * v){return _gl_loader_glcolor4dv(v);}
inline void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){return _gl_loader_glcolor4f(red, green, blue, alpha);}
inline void glColor4fv(const GLfloat * v){return _gl_loader_glcolor4fv(v);}
inline void glColor4i(GLint red, GLint green, GLint blue, GLint alpha){return _gl_loader_glcolor4i(red, green, blue, alpha);}
inline void glColor4iv(const GLint * v){return _gl_loader_glcolor4iv(v);}
inline void glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha){return _gl_loader_glcolor4s(red, green, blue, alpha);}
inline void glColor4sv(const GLshort * v){return _gl_loader_glcolor4sv(v);}
inline void glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha){return _gl_loader_glcolor4ub(red, green, blue, alpha);}
inline void glColor4ubv(const GLubyte * v){return _gl_loader_glcolor4ubv(v);}
inline void glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha){return _gl_loader_glcolor4ui(red, green, blue, alpha);}
inline void glColor4uiv(const GLuint * v){return _gl_loader_glcolor4uiv(v);}
inline void glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha){return _gl_loader_glcolor4us(red, green, blue, alpha);}
inline void glColor4usv(const GLushort * v){return _gl_loader_glcolor4usv(v);}
inline void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha){return _gl_loader_glcolormask(red, green, blue, alpha);}
inline void glColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a){return _gl_loader_glcolormaski(index, r, g, b, a);}
inline void glColorMaterial(GLenum face, GLenum mode){return _gl_loader_glcolormaterial(face, mode);}
inline void glColorP3ui(GLenum type, GLuint color){return _gl_loader_glcolorp3ui(type, color);}
inline void glColorP3uiv(GLenum type, const GLuint * color){return _gl_loader_glcolorp3uiv(type, color);}
inline void glColorP4ui(GLenum type, GLuint color){return _gl_loader_glcolorp4ui(type, color);}
inline void glColorP4uiv(GLenum type, const GLuint * color){return _gl_loader_glcolorp4uiv(type, color);}
inline void glColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glcolorpointer(size, type, stride, pointer);}
inline void glCompileShader(GLuint shader){return _gl_loader_glcompileshader(shader);}
inline void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const void * data){return _gl_loader_glcompressedteximage1d(target, level, internalformat, width, border, imageSize, data);}
inline void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data){return _gl_loader_glcompressedteximage2d(target, level, internalformat, width, height, border, imageSize, data);}
inline void glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const void * data){return _gl_loader_glcompressedteximage3d(target, level, internalformat, width, height, depth, border, imageSize, data);}
inline void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexsubimage1d(target, level, xoffset, width, format, imageSize, data);}
inline void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexsubimage2d(target, level, xoffset, yoffset, width, height, format, imageSize, data);}
inline void glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexsubimage3d(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
inline void glCompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexturesubimage1d(texture, level, xoffset, width, format, imageSize, data);}
inline void glCompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexturesubimage2d(texture, level, xoffset, yoffset, width, height, format, imageSize, data);}
inline void glCompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const void * data){return _gl_loader_glcompressedtexturesubimage3d(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);}
inline void glCopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){return _gl_loader_glcopybuffersubdata(readTarget, writeTarget, readOffset, writeOffset, size);}
inline void glCopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth){return _gl_loader_glcopyimagesubdata(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);}
inline void glCopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size){return _gl_loader_glcopynamedbuffersubdata(readBuffer, writeBuffer, readOffset, writeOffset, size);}
inline void glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type){return _gl_loader_glcopypixels(x, y, width, height, type);}
inline void glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border){return _gl_loader_glcopyteximage1d(target, level, internalformat, x, y, width, border);}
inline void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border){return _gl_loader_glcopyteximage2d(target, level, internalformat, x, y, width, height, border);}
inline void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){return _gl_loader_glcopytexsubimage1d(target, level, xoffset, x, y, width);}
inline void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glcopytexsubimage2d(target, level, xoffset, yoffset, x, y, width, height);}
inline void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glcopytexsubimage3d(target, level, xoffset, yoffset, zoffset, x, y, width, height);}
inline void glCopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width){return _gl_loader_glcopytexturesubimage1d(texture, level, xoffset, x, y, width);}
inline void glCopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glcopytexturesubimage2d(texture, level, xoffset, yoffset, x, y, width, height);}
inline void glCopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glcopytexturesubimage3d(texture, level, xoffset, yoffset, zoffset, x, y, width, height);}
inline void glCreateBuffers(GLsizei n, GLuint * buffers){return _gl_loader_glcreatebuffers(n, buffers);}
inline void glCreateFramebuffers(GLsizei n, GLuint * framebuffers){return _gl_loader_glcreateframebuffers(n, framebuffers);}
inline GLuint glCreateProgram(){return _gl_loader_glcreateprogram();}
inline void glCreateProgramPipelines(GLsizei n, GLuint * pipelines){return _gl_loader_glcreateprogrampipelines(n, pipelines);}
inline void glCreateQueries(GLenum target, GLsizei n, GLuint * ids){return _gl_loader_glcreatequeries(target, n, ids);}
inline void glCreateRenderbuffers(GLsizei n, GLuint * renderbuffers){return _gl_loader_glcreaterenderbuffers(n, renderbuffers);}
inline void glCreateSamplers(GLsizei n, GLuint * samplers){return _gl_loader_glcreatesamplers(n, samplers);}
inline GLuint glCreateShader(GLenum type){return _gl_loader_glcreateshader(type);}
inline GLuint glCreateShaderProgramv(GLenum type, GLsizei count, const GLchar * const * strings){return _gl_loader_glcreateshaderprogramv(type, count, strings);}
inline void glCreateTextures(GLenum target, GLsizei n, GLuint * textures){return _gl_loader_glcreatetextures(target, n, textures);}
inline void glCreateTransformFeedbacks(GLsizei n, GLuint * ids){return _gl_loader_glcreatetransformfeedbacks(n, ids);}
inline void glCreateVertexArrays(GLsizei n, GLuint * arrays){return _gl_loader_glcreatevertexarrays(n, arrays);}
inline void glCullFace(GLenum mode){return _gl_loader_glcullface(mode);}
inline void glDebugMessageCallback(GLDEBUGPROC callback, const void * userParam){return _gl_loader_gldebugmessagecallback(callback, userParam);}
inline void glDebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled){return _gl_loader_gldebugmessagecontrol(source, type, severity, count, ids, enabled);}
inline void glDebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf){return _gl_loader_gldebugmessageinsert(source, type, id, severity, length, buf);}
inline void glDeleteBuffers(GLsizei n, const GLuint * buffers){return _gl_loader_gldeletebuffers(n, buffers);}
inline void glDeleteFramebuffers(GLsizei n, const GLuint * framebuffers){return _gl_loader_gldeleteframebuffers(n, framebuffers);}
inline void glDeleteLists(GLuint list, GLsizei range){return _gl_loader_gldeletelists(list, range);}
inline void glDeleteProgram(GLuint program){return _gl_loader_gldeleteprogram(program);}
inline void glDeleteProgramPipelines(GLsizei n, const GLuint * pipelines){return _gl_loader_gldeleteprogrampipelines(n, pipelines);}
inline void glDeleteQueries(GLsizei n, const GLuint * ids){return _gl_loader_gldeletequeries(n, ids);}
inline void glDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers){return _gl_loader_gldeleterenderbuffers(n, renderbuffers);}
inline void glDeleteSamplers(GLsizei count, const GLuint * samplers){return _gl_loader_gldeletesamplers(count, samplers);}
inline void glDeleteShader(GLuint shader){return _gl_loader_gldeleteshader(shader);}
inline void glDeleteSync(GLsync sync){return _gl_loader_gldeletesync(sync);}
inline void glDeleteTextures(GLsizei n, const GLuint * textures){return _gl_loader_gldeletetextures(n, textures);}
inline void glDeleteTransformFeedbacks(GLsizei n, const GLuint * ids){return _gl_loader_gldeletetransformfeedbacks(n, ids);}
inline void glDeleteVertexArrays(GLsizei n, const GLuint * arrays){return _gl_loader_gldeletevertexarrays(n, arrays);}
inline void glDepthFunc(GLenum func){return _gl_loader_gldepthfunc(func);}
inline void glDepthMask(GLboolean flag){return _gl_loader_gldepthmask(flag);}
inline void glDepthRange(GLdouble n, GLdouble f){return _gl_loader_gldepthrange(n, f);}
inline void glDepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v){return _gl_loader_gldepthrangearrayv(first, count, v);}
inline void glDepthRangeIndexed(GLuint index, GLdouble n, GLdouble f){return _gl_loader_gldepthrangeindexed(index, n, f);}
inline void glDepthRangef(GLfloat n, GLfloat f){return _gl_loader_gldepthrangef(n, f);}
inline void glDetachShader(GLuint program, GLuint shader){return _gl_loader_gldetachshader(program, shader);}
inline void glDisable(GLenum cap){return _gl_loader_gldisable(cap);}
inline void glDisableClientState(GLenum array){return _gl_loader_gldisableclientstate(array);}
inline void glDisableVertexArrayAttrib(GLuint vaobj, GLuint index){return _gl_loader_gldisablevertexarrayattrib(vaobj, index);}
inline void glDisableVertexAttribArray(GLuint index){return _gl_loader_gldisablevertexattribarray(index);}
inline void glDisablei(GLenum target, GLuint index){return _gl_loader_gldisablei(target, index);}
inline void glDispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z){return _gl_loader_gldispatchcompute(num_groups_x, num_groups_y, num_groups_z);}
inline void glDispatchComputeIndirect(GLintptr indirect){return _gl_loader_gldispatchcomputeindirect(indirect);}
inline void glDrawArrays(GLenum mode, GLint first, GLsizei count){return _gl_loader_gldrawarrays(mode, first, count);}
inline void glDrawArraysIndirect(GLenum mode, const void * indirect){return _gl_loader_gldrawarraysindirect(mode, indirect);}
inline void glDrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount){return _gl_loader_gldrawarraysinstanced(mode, first, count, instancecount);}
inline void glDrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance){return _gl_loader_gldrawarraysinstancedbaseinstance(mode, first, count, instancecount, baseinstance);}
inline void glDrawBuffer(GLenum buf){return _gl_loader_gldrawbuffer(buf);}
inline void glDrawBuffers(GLsizei n, const GLenum * bufs){return _gl_loader_gldrawbuffers(n, bufs);}
inline void glDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices){return _gl_loader_gldrawelements(mode, count, type, indices);}
inline void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLint basevertex){return _gl_loader_gldrawelementsbasevertex(mode, count, type, indices, basevertex);}
inline void glDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect){return _gl_loader_gldrawelementsindirect(mode, type, indirect);}
inline void glDrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount){return _gl_loader_gldrawelementsinstanced(mode, count, type, indices, instancecount);}
inline void glDrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLuint baseinstance){return _gl_loader_gldrawelementsinstancedbaseinstance(mode, count, type, indices, instancecount, baseinstance);}
inline void glDrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex){return _gl_loader_gldrawelementsinstancedbasevertex(mode, count, type, indices, instancecount, basevertex);}
inline void glDrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const void * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance){return _gl_loader_gldrawelementsinstancedbasevertexbaseinstance(mode, count, type, indices, instancecount, basevertex, baseinstance);}
inline void glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){return _gl_loader_gldrawpixels(width, height, format, type, pixels);}
inline void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices){return _gl_loader_gldrawrangeelements(mode, start, end, count, type, indices);}
inline void glDrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void * indices, GLint basevertex){return _gl_loader_gldrawrangeelementsbasevertex(mode, start, end, count, type, indices, basevertex);}
inline void glDrawTransformFeedback(GLenum mode, GLuint id){return _gl_loader_gldrawtransformfeedback(mode, id);}
inline void glDrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount){return _gl_loader_gldrawtransformfeedbackinstanced(mode, id, instancecount);}
inline void glDrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream){return _gl_loader_gldrawtransformfeedbackstream(mode, id, stream);}
inline void glDrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount){return _gl_loader_gldrawtransformfeedbackstreaminstanced(mode, id, stream, instancecount);}
inline void glEdgeFlag(GLboolean flag){return _gl_loader_gledgeflag(flag);}
inline void glEdgeFlagPointer(GLsizei stride, const void * pointer){return _gl_loader_gledgeflagpointer(stride, pointer);}
inline void glEdgeFlagv(const GLboolean * flag){return _gl_loader_gledgeflagv(flag);}
inline void glEnable(GLenum cap){return _gl_loader_glenable(cap);}
inline void glEnableClientState(GLenum array){return _gl_loader_glenableclientstate(array);}
inline void glEnableVertexArrayAttrib(GLuint vaobj, GLuint index){return _gl_loader_glenablevertexarrayattrib(vaobj, index);}
inline void glEnableVertexAttribArray(GLuint index){return _gl_loader_glenablevertexattribarray(index);}
inline void glEnablei(GLenum target, GLuint index){return _gl_loader_glenablei(target, index);}
inline void glEnd(){return _gl_loader_glend();}
inline void glEndConditionalRender(){return _gl_loader_glendconditionalrender();}
inline void glEndList(){return _gl_loader_glendlist();}
inline void glEndQuery(GLenum target){return _gl_loader_glendquery(target);}
inline void glEndQueryIndexed(GLenum target, GLuint index){return _gl_loader_glendqueryindexed(target, index);}
inline void glEndTransformFeedback(){return _gl_loader_glendtransformfeedback();}
inline void glEvalCoord1d(GLdouble u){return _gl_loader_glevalcoord1d(u);}
inline void glEvalCoord1dv(const GLdouble * u){return _gl_loader_glevalcoord1dv(u);}
inline void glEvalCoord1f(GLfloat u){return _gl_loader_glevalcoord1f(u);}
inline void glEvalCoord1fv(const GLfloat * u){return _gl_loader_glevalcoord1fv(u);}
inline void glEvalCoord2d(GLdouble u, GLdouble v){return _gl_loader_glevalcoord2d(u, v);}
inline void glEvalCoord2dv(const GLdouble * u){return _gl_loader_glevalcoord2dv(u);}
inline void glEvalCoord2f(GLfloat u, GLfloat v){return _gl_loader_glevalcoord2f(u, v);}
inline void glEvalCoord2fv(const GLfloat * u){return _gl_loader_glevalcoord2fv(u);}
inline void glEvalMesh1(GLenum mode, GLint i1, GLint i2){return _gl_loader_glevalmesh1(mode, i1, i2);}
inline void glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2){return _gl_loader_glevalmesh2(mode, i1, i2, j1, j2);}
inline void glEvalPoint1(GLint i){return _gl_loader_glevalpoint1(i);}
inline void glEvalPoint2(GLint i, GLint j){return _gl_loader_glevalpoint2(i, j);}
inline void glFeedbackBuffer(GLsizei size, GLenum type, GLfloat * buffer){return _gl_loader_glfeedbackbuffer(size, type, buffer);}
inline GLsync glFenceSync(GLenum condition, GLbitfield flags){return _gl_loader_glfencesync(condition, flags);}
inline void glFinish(){return _gl_loader_glfinish();}
inline void glFlush(){return _gl_loader_glflush();}
inline void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length){return _gl_loader_glflushmappedbufferrange(target, offset, length);}
inline void glFlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length){return _gl_loader_glflushmappednamedbufferrange(buffer, offset, length);}
inline void glFogCoordPointer(GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glfogcoordpointer(type, stride, pointer);}
inline void glFogCoordd(GLdouble coord){return _gl_loader_glfogcoordd(coord);}
inline void glFogCoorddv(const GLdouble * coord){return _gl_loader_glfogcoorddv(coord);}
inline void glFogCoordf(GLfloat coord){return _gl_loader_glfogcoordf(coord);}
inline void glFogCoordfv(const GLfloat * coord){return _gl_loader_glfogcoordfv(coord);}
inline void glFogf(GLenum pname, GLfloat param){return _gl_loader_glfogf(pname, param);}
inline void glFogfv(GLenum pname, const GLfloat * params){return _gl_loader_glfogfv(pname, params);}
inline void glFogi(GLenum pname, GLint param){return _gl_loader_glfogi(pname, param);}
inline void glFogiv(GLenum pname, const GLint * params){return _gl_loader_glfogiv(pname, params);}
inline void glFramebufferParameteri(GLenum target, GLenum pname, GLint param){return _gl_loader_glframebufferparameteri(target, pname, param);}
inline void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){return _gl_loader_glframebufferrenderbuffer(target, attachment, renderbuffertarget, renderbuffer);}
inline void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level){return _gl_loader_glframebuffertexture(target, attachment, texture, level);}
inline void glFramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){return _gl_loader_glframebuffertexture1d(target, attachment, textarget, texture, level);}
inline void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level){return _gl_loader_glframebuffertexture2d(target, attachment, textarget, texture, level);}
inline void glFramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset){return _gl_loader_glframebuffertexture3d(target, attachment, textarget, texture, level, zoffset);}
inline void glFramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer){return _gl_loader_glframebuffertexturelayer(target, attachment, texture, level, layer);}
inline void glFrontFace(GLenum mode){return _gl_loader_glfrontface(mode);}
inline void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){return _gl_loader_glfrustum(left, right, bottom, top, zNear, zFar);}
inline void glGenBuffers(GLsizei n, GLuint * buffers){return _gl_loader_glgenbuffers(n, buffers);}
inline void glGenFramebuffers(GLsizei n, GLuint * framebuffers){return _gl_loader_glgenframebuffers(n, framebuffers);}
inline GLuint glGenLists(GLsizei range){return _gl_loader_glgenlists(range);}
inline void glGenProgramPipelines(GLsizei n, GLuint * pipelines){return _gl_loader_glgenprogrampipelines(n, pipelines);}
inline void glGenQueries(GLsizei n, GLuint * ids){return _gl_loader_glgenqueries(n, ids);}
inline void glGenRenderbuffers(GLsizei n, GLuint * renderbuffers){return _gl_loader_glgenrenderbuffers(n, renderbuffers);}
inline void glGenSamplers(GLsizei count, GLuint * samplers){return _gl_loader_glgensamplers(count, samplers);}
inline void glGenTextures(GLsizei n, GLuint * textures){return _gl_loader_glgentextures(n, textures);}
inline void glGenTransformFeedbacks(GLsizei n, GLuint * ids){return _gl_loader_glgentransformfeedbacks(n, ids);}
inline void glGenVertexArrays(GLsizei n, GLuint * arrays){return _gl_loader_glgenvertexarrays(n, arrays);}
inline void glGenerateMipmap(GLenum target){return _gl_loader_glgeneratemipmap(target);}
inline void glGenerateTextureMipmap(GLuint texture){return _gl_loader_glgeneratetexturemipmap(texture);}
inline void glGetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params){return _gl_loader_glgetactiveatomiccounterbufferiv(program, bufferIndex, pname, params);}
inline void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){return _gl_loader_glgetactiveattrib(program, index, bufSize, length, size, type, name);}
inline void glGetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name){return _gl_loader_glgetactivesubroutinename(program, shadertype, index, bufSize, length, name);}
inline void glGetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name){return _gl_loader_glgetactivesubroutineuniformname(program, shadertype, index, bufSize, length, name);}
inline void glGetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values){return _gl_loader_glgetactivesubroutineuniformiv(program, shadertype, index, pname, values);}
inline void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name){return _gl_loader_glgetactiveuniform(program, index, bufSize, length, size, type, name);}
inline void glGetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName){return _gl_loader_glgetactiveuniformblockname(program, uniformBlockIndex, bufSize, length, uniformBlockName);}
inline void glGetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params){return _gl_loader_glgetactiveuniformblockiv(program, uniformBlockIndex, pname, params);}
inline void glGetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName){return _gl_loader_glgetactiveuniformname(program, uniformIndex, bufSize, length, uniformName);}
inline void glGetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params){return _gl_loader_glgetactiveuniformsiv(program, uniformCount, uniformIndices, pname, params);}
inline void glGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders){return _gl_loader_glgetattachedshaders(program, maxCount, count, shaders);}
inline GLint glGetAttribLocation(GLuint program, const GLchar * name){return _gl_loader_glgetattriblocation(program, name);}
inline void glGetBooleani_v(GLenum target, GLuint index, GLboolean * data){return _gl_loader_glgetbooleani_v(target, index, data);}
inline void glGetBooleanv(GLenum pname, GLboolean * data){return _gl_loader_glgetbooleanv(pname, data);}
inline void glGetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params){return _gl_loader_glgetbufferparameteri64v(target, pname, params);}
inline void glGetBufferParameteriv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgetbufferparameteriv(target, pname, params);}
inline void glGetBufferPointerv(GLenum target, GLenum pname, void * * params){return _gl_loader_glgetbufferpointerv(target, pname, params);}
inline void glGetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, void * data){return _gl_loader_glgetbuffersubdata(target, offset, size, data);}
inline void glGetClipPlane(GLenum plane, GLdouble * equation){return _gl_loader_glgetclipplane(plane, equation);}
inline void glGetCompressedTexImage(GLenum target, GLint level, void * img){return _gl_loader_glgetcompressedteximage(target, level, img);}
inline void glGetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, void * pixels){return _gl_loader_glgetcompressedtextureimage(texture, level, bufSize, pixels);}
inline void glGetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, void * pixels){return _gl_loader_glgetcompressedtexturesubimage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);}
inline GLuint glGetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog){return _gl_loader_glgetdebugmessagelog(count, bufSize, sources, types, ids, severities, lengths, messageLog);}
inline void glGetDoublei_v(GLenum target, GLuint index, GLdouble * data){return _gl_loader_glgetdoublei_v(target, index, data);}
inline void glGetDoublev(GLenum pname, GLdouble * data){return _gl_loader_glgetdoublev(pname, data);}
inline GLenum glGetError(){return _gl_loader_glgeterror();}
inline void glGetFloati_v(GLenum target, GLuint index, GLfloat * data){return _gl_loader_glgetfloati_v(target, index, data);}
inline void glGetFloatv(GLenum pname, GLfloat * data){return _gl_loader_glgetfloatv(pname, data);}
inline GLint glGetFragDataIndex(GLuint program, const GLchar * name){return _gl_loader_glgetfragdataindex(program, name);}
inline GLint glGetFragDataLocation(GLuint program, const GLchar * name){return _gl_loader_glgetfragdatalocation(program, name);}
inline void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params){return _gl_loader_glgetframebufferattachmentparameteriv(target, attachment, pname, params);}
inline void glGetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgetframebufferparameteriv(target, pname, params);}
inline GLenum glGetGraphicsResetStatus(){return _gl_loader_glgetgraphicsresetstatus();}
inline void glGetInteger64i_v(GLenum target, GLuint index, GLint64 * data){return _gl_loader_glgetinteger64i_v(target, index, data);}
inline void glGetInteger64v(GLenum pname, GLint64 * data){return _gl_loader_glgetinteger64v(pname, data);}
inline void glGetIntegeri_v(GLenum target, GLuint index, GLint * data){return _gl_loader_glgetintegeri_v(target, index, data);}
inline void glGetIntegerv(GLenum pname, GLint * data){return _gl_loader_glgetintegerv(pname, data);}
inline void glGetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint64 * params){return _gl_loader_glgetinternalformati64v(target, internalformat, pname, count, params);}
inline void glGetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei count, GLint * params){return _gl_loader_glgetinternalformativ(target, internalformat, pname, count, params);}
inline void glGetLightfv(GLenum light, GLenum pname, GLfloat * params){return _gl_loader_glgetlightfv(light, pname, params);}
inline void glGetLightiv(GLenum light, GLenum pname, GLint * params){return _gl_loader_glgetlightiv(light, pname, params);}
inline void glGetMapdv(GLenum target, GLenum query, GLdouble * v){return _gl_loader_glgetmapdv(target, query, v);}
inline void glGetMapfv(GLenum target, GLenum query, GLfloat * v){return _gl_loader_glgetmapfv(target, query, v);}
inline void glGetMapiv(GLenum target, GLenum query, GLint * v){return _gl_loader_glgetmapiv(target, query, v);}
inline void glGetMaterialfv(GLenum face, GLenum pname, GLfloat * params){return _gl_loader_glgetmaterialfv(face, pname, params);}
inline void glGetMaterialiv(GLenum face, GLenum pname, GLint * params){return _gl_loader_glgetmaterialiv(face, pname, params);}
inline void glGetMultisamplefv(GLenum pname, GLuint index, GLfloat * val){return _gl_loader_glgetmultisamplefv(pname, index, val);}
inline void glGetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params){return _gl_loader_glgetnamedbufferparameteri64v(buffer, pname, params);}
inline void glGetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params){return _gl_loader_glgetnamedbufferparameteriv(buffer, pname, params);}
inline void glGetNamedBufferPointerv(GLuint buffer, GLenum pname, void * * params){return _gl_loader_glgetnamedbufferpointerv(buffer, pname, params);}
inline void glGetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, void * data){return _gl_loader_glgetnamedbuffersubdata(buffer, offset, size, data);}
inline void glGetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params){return _gl_loader_glgetnamedframebufferattachmentparameteriv(framebuffer, attachment, pname, params);}
inline void glGetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param){return _gl_loader_glgetnamedframebufferparameteriv(framebuffer, pname, param);}
inline void glGetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params){return _gl_loader_glgetnamedrenderbufferparameteriv(renderbuffer, pname, params);}
inline void glGetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label){return _gl_loader_glgetobjectlabel(identifier, name, bufSize, length, label);}
inline void glGetObjectPtrLabel(const void * ptr, GLsizei bufSize, GLsizei * length, GLchar * label){return _gl_loader_glgetobjectptrlabel(ptr, bufSize, length, label);}
inline void glGetPixelMapfv(GLenum map, GLfloat * values){return _gl_loader_glgetpixelmapfv(map, values);}
inline void glGetPixelMapuiv(GLenum map, GLuint * values){return _gl_loader_glgetpixelmapuiv(map, values);}
inline void glGetPixelMapusv(GLenum map, GLushort * values){return _gl_loader_glgetpixelmapusv(map, values);}
inline void glGetPointerv(GLenum pname, void * * params){return _gl_loader_glgetpointerv(pname, params);}
inline void glGetPolygonStipple(GLubyte * mask){return _gl_loader_glgetpolygonstipple(mask);}
inline void glGetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, void * binary){return _gl_loader_glgetprogrambinary(program, bufSize, length, binaryFormat, binary);}
inline void glGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog){return _gl_loader_glgetprograminfolog(program, bufSize, length, infoLog);}
inline void glGetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params){return _gl_loader_glgetprograminterfaceiv(program, programInterface, pname, params);}
inline void glGetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog){return _gl_loader_glgetprogrampipelineinfolog(pipeline, bufSize, length, infoLog);}
inline void glGetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params){return _gl_loader_glgetprogrampipelineiv(pipeline, pname, params);}
inline GLuint glGetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name){return _gl_loader_glgetprogramresourceindex(program, programInterface, name);}
inline GLint glGetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name){return _gl_loader_glgetprogramresourcelocation(program, programInterface, name);}
inline GLint glGetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name){return _gl_loader_glgetprogramresourcelocationindex(program, programInterface, name);}
inline void glGetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name){return _gl_loader_glgetprogramresourcename(program, programInterface, index, bufSize, length, name);}
inline void glGetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei count, GLsizei * length, GLint * params){return _gl_loader_glgetprogramresourceiv(program, programInterface, index, propCount, props, count, length, params);}
inline void glGetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values){return _gl_loader_glgetprogramstageiv(program, shadertype, pname, values);}
inline void glGetProgramiv(GLuint program, GLenum pname, GLint * params){return _gl_loader_glgetprogramiv(program, pname, params);}
inline void glGetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){return _gl_loader_glgetquerybufferobjecti64v(id, buffer, pname, offset);}
inline void glGetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){return _gl_loader_glgetquerybufferobjectiv(id, buffer, pname, offset);}
inline void glGetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){return _gl_loader_glgetquerybufferobjectui64v(id, buffer, pname, offset);}
inline void glGetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset){return _gl_loader_glgetquerybufferobjectuiv(id, buffer, pname, offset);}
inline void glGetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params){return _gl_loader_glgetqueryindexediv(target, index, pname, params);}
inline void glGetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params){return _gl_loader_glgetqueryobjecti64v(id, pname, params);}
inline void glGetQueryObjectiv(GLuint id, GLenum pname, GLint * params){return _gl_loader_glgetqueryobjectiv(id, pname, params);}
inline void glGetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params){return _gl_loader_glgetqueryobjectui64v(id, pname, params);}
inline void glGetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params){return _gl_loader_glgetqueryobjectuiv(id, pname, params);}
inline void glGetQueryiv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgetqueryiv(target, pname, params);}
inline void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgetrenderbufferparameteriv(target, pname, params);}
inline void glGetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params){return _gl_loader_glgetsamplerparameteriiv(sampler, pname, params);}
inline void glGetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params){return _gl_loader_glgetsamplerparameteriuiv(sampler, pname, params);}
inline void glGetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params){return _gl_loader_glgetsamplerparameterfv(sampler, pname, params);}
inline void glGetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params){return _gl_loader_glgetsamplerparameteriv(sampler, pname, params);}
inline void glGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog){return _gl_loader_glgetshaderinfolog(shader, bufSize, length, infoLog);}
inline void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision){return _gl_loader_glgetshaderprecisionformat(shadertype, precisiontype, range, precision);}
inline void glGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source){return _gl_loader_glgetshadersource(shader, bufSize, length, source);}
inline void glGetShaderiv(GLuint shader, GLenum pname, GLint * params){return _gl_loader_glgetshaderiv(shader, pname, params);}
inline GLubyte glGetString(GLenum name){return _gl_loader_glgetstring(name);}
inline GLubyte glGetStringi(GLenum name, GLuint index){return _gl_loader_glgetstringi(name, index);}
inline GLuint glGetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name){return _gl_loader_glgetsubroutineindex(program, shadertype, name);}
inline GLint glGetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name){return _gl_loader_glgetsubroutineuniformlocation(program, shadertype, name);}
inline void glGetSynciv(GLsync sync, GLenum pname, GLsizei count, GLsizei * length, GLint * values){return _gl_loader_glgetsynciv(sync, pname, count, length, values);}
inline void glGetTexEnvfv(GLenum target, GLenum pname, GLfloat * params){return _gl_loader_glgettexenvfv(target, pname, params);}
inline void glGetTexEnviv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgettexenviv(target, pname, params);}
inline void glGetTexGendv(GLenum coord, GLenum pname, GLdouble * params){return _gl_loader_glgettexgendv(coord, pname, params);}
inline void glGetTexGenfv(GLenum coord, GLenum pname, GLfloat * params){return _gl_loader_glgettexgenfv(coord, pname, params);}
inline void glGetTexGeniv(GLenum coord, GLenum pname, GLint * params){return _gl_loader_glgettexgeniv(coord, pname, params);}
inline void glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, void * pixels){return _gl_loader_glgetteximage(target, level, format, type, pixels);}
inline void glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params){return _gl_loader_glgettexlevelparameterfv(target, level, pname, params);}
inline void glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params){return _gl_loader_glgettexlevelparameteriv(target, level, pname, params);}
inline void glGetTexParameterIiv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgettexparameteriiv(target, pname, params);}
inline void glGetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params){return _gl_loader_glgettexparameteriuiv(target, pname, params);}
inline void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params){return _gl_loader_glgettexparameterfv(target, pname, params);}
inline void glGetTexParameteriv(GLenum target, GLenum pname, GLint * params){return _gl_loader_glgettexparameteriv(target, pname, params);}
inline void glGetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels){return _gl_loader_glgettextureimage(texture, level, format, type, bufSize, pixels);}
inline void glGetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params){return _gl_loader_glgettexturelevelparameterfv(texture, level, pname, params);}
inline void glGetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params){return _gl_loader_glgettexturelevelparameteriv(texture, level, pname, params);}
inline void glGetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params){return _gl_loader_glgettextureparameteriiv(texture, pname, params);}
inline void glGetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params){return _gl_loader_glgettextureparameteriuiv(texture, pname, params);}
inline void glGetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params){return _gl_loader_glgettextureparameterfv(texture, pname, params);}
inline void glGetTextureParameteriv(GLuint texture, GLenum pname, GLint * params){return _gl_loader_glgettextureparameteriv(texture, pname, params);}
inline void glGetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, void * pixels){return _gl_loader_glgettexturesubimage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);}
inline void glGetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name){return _gl_loader_glgettransformfeedbackvarying(program, index, bufSize, length, size, type, name);}
inline void glGetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param){return _gl_loader_glgettransformfeedbacki64_v(xfb, pname, index, param);}
inline void glGetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param){return _gl_loader_glgettransformfeedbacki_v(xfb, pname, index, param);}
inline void glGetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param){return _gl_loader_glgettransformfeedbackiv(xfb, pname, param);}
inline GLuint glGetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName){return _gl_loader_glgetuniformblockindex(program, uniformBlockName);}
inline void glGetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar * const * uniformNames, GLuint * uniformIndices){return _gl_loader_glgetuniformindices(program, uniformCount, uniformNames, uniformIndices);}
inline GLint glGetUniformLocation(GLuint program, const GLchar * name){return _gl_loader_glgetuniformlocation(program, name);}
inline void glGetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params){return _gl_loader_glgetuniformsubroutineuiv(shadertype, location, params);}
inline void glGetUniformdv(GLuint program, GLint location, GLdouble * params){return _gl_loader_glgetuniformdv(program, location, params);}
inline void glGetUniformfv(GLuint program, GLint location, GLfloat * params){return _gl_loader_glgetuniformfv(program, location, params);}
inline void glGetUniformiv(GLuint program, GLint location, GLint * params){return _gl_loader_glgetuniformiv(program, location, params);}
inline void glGetUniformuiv(GLuint program, GLint location, GLuint * params){return _gl_loader_glgetuniformuiv(program, location, params);}
inline void glGetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param){return _gl_loader_glgetvertexarrayindexed64iv(vaobj, index, pname, param);}
inline void glGetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param){return _gl_loader_glgetvertexarrayindexediv(vaobj, index, pname, param);}
inline void glGetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param){return _gl_loader_glgetvertexarrayiv(vaobj, pname, param);}
inline void glGetVertexAttribIiv(GLuint index, GLenum pname, GLint * params){return _gl_loader_glgetvertexattribiiv(index, pname, params);}
inline void glGetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params){return _gl_loader_glgetvertexattribiuiv(index, pname, params);}
inline void glGetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params){return _gl_loader_glgetvertexattribldv(index, pname, params);}
inline void glGetVertexAttribPointerv(GLuint index, GLenum pname, void * * pointer){return _gl_loader_glgetvertexattribpointerv(index, pname, pointer);}
inline void glGetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params){return _gl_loader_glgetvertexattribdv(index, pname, params);}
inline void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params){return _gl_loader_glgetvertexattribfv(index, pname, params);}
inline void glGetVertexAttribiv(GLuint index, GLenum pname, GLint * params){return _gl_loader_glgetvertexattribiv(index, pname, params);}
inline void glGetnColorTable(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * table){return _gl_loader_glgetncolortable(target, format, type, bufSize, table);}
inline void glGetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, void * pixels){return _gl_loader_glgetncompressedteximage(target, lod, bufSize, pixels);}
inline void glGetnConvolutionFilter(GLenum target, GLenum format, GLenum type, GLsizei bufSize, void * image){return _gl_loader_glgetnconvolutionfilter(target, format, type, bufSize, image);}
inline void glGetnHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values){return _gl_loader_glgetnhistogram(target, reset, format, type, bufSize, values);}
inline void glGetnMapdv(GLenum target, GLenum query, GLsizei bufSize, GLdouble * v){return _gl_loader_glgetnmapdv(target, query, bufSize, v);}
inline void glGetnMapfv(GLenum target, GLenum query, GLsizei bufSize, GLfloat * v){return _gl_loader_glgetnmapfv(target, query, bufSize, v);}
inline void glGetnMapiv(GLenum target, GLenum query, GLsizei bufSize, GLint * v){return _gl_loader_glgetnmapiv(target, query, bufSize, v);}
inline void glGetnMinmax(GLenum target, GLboolean reset, GLenum format, GLenum type, GLsizei bufSize, void * values){return _gl_loader_glgetnminmax(target, reset, format, type, bufSize, values);}
inline void glGetnPixelMapfv(GLenum map, GLsizei bufSize, GLfloat * values){return _gl_loader_glgetnpixelmapfv(map, bufSize, values);}
inline void glGetnPixelMapuiv(GLenum map, GLsizei bufSize, GLuint * values){return _gl_loader_glgetnpixelmapuiv(map, bufSize, values);}
inline void glGetnPixelMapusv(GLenum map, GLsizei bufSize, GLushort * values){return _gl_loader_glgetnpixelmapusv(map, bufSize, values);}
inline void glGetnPolygonStipple(GLsizei bufSize, GLubyte * pattern){return _gl_loader_glgetnpolygonstipple(bufSize, pattern);}
inline void glGetnSeparableFilter(GLenum target, GLenum format, GLenum type, GLsizei rowBufSize, void * row, GLsizei columnBufSize, void * column, void * span){return _gl_loader_glgetnseparablefilter(target, format, type, rowBufSize, row, columnBufSize, column, span);}
inline void glGetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, void * pixels){return _gl_loader_glgetnteximage(target, level, format, type, bufSize, pixels);}
inline void glGetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params){return _gl_loader_glgetnuniformdv(program, location, bufSize, params);}
inline void glGetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params){return _gl_loader_glgetnuniformfv(program, location, bufSize, params);}
inline void glGetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params){return _gl_loader_glgetnuniformiv(program, location, bufSize, params);}
inline void glGetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params){return _gl_loader_glgetnuniformuiv(program, location, bufSize, params);}
inline void glHint(GLenum target, GLenum mode){return _gl_loader_glhint(target, mode);}
inline void glIndexMask(GLuint mask){return _gl_loader_glindexmask(mask);}
inline void glIndexPointer(GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glindexpointer(type, stride, pointer);}
inline void glIndexd(GLdouble c){return _gl_loader_glindexd(c);}
inline void glIndexdv(const GLdouble * c){return _gl_loader_glindexdv(c);}
inline void glIndexf(GLfloat c){return _gl_loader_glindexf(c);}
inline void glIndexfv(const GLfloat * c){return _gl_loader_glindexfv(c);}
inline void glIndexi(GLint c){return _gl_loader_glindexi(c);}
inline void glIndexiv(const GLint * c){return _gl_loader_glindexiv(c);}
inline void glIndexs(GLshort c){return _gl_loader_glindexs(c);}
inline void glIndexsv(const GLshort * c){return _gl_loader_glindexsv(c);}
inline void glIndexub(GLubyte c){return _gl_loader_glindexub(c);}
inline void glIndexubv(const GLubyte * c){return _gl_loader_glindexubv(c);}
inline void glInitNames(){return _gl_loader_glinitnames();}
inline void glInterleavedArrays(GLenum format, GLsizei stride, const void * pointer){return _gl_loader_glinterleavedarrays(format, stride, pointer);}
inline void glInvalidateBufferData(GLuint buffer){return _gl_loader_glinvalidatebufferdata(buffer);}
inline void glInvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length){return _gl_loader_glinvalidatebuffersubdata(buffer, offset, length);}
inline void glInvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments){return _gl_loader_glinvalidateframebuffer(target, numAttachments, attachments);}
inline void glInvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments){return _gl_loader_glinvalidatenamedframebufferdata(framebuffer, numAttachments, attachments);}
inline void glInvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glinvalidatenamedframebuffersubdata(framebuffer, numAttachments, attachments, x, y, width, height);}
inline void glInvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glinvalidatesubframebuffer(target, numAttachments, attachments, x, y, width, height);}
inline void glInvalidateTexImage(GLuint texture, GLint level){return _gl_loader_glinvalidateteximage(texture, level);}
inline void glInvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth){return _gl_loader_glinvalidatetexsubimage(texture, level, xoffset, yoffset, zoffset, width, height, depth);}
inline GLboolean glIsBuffer(GLuint buffer){return _gl_loader_glisbuffer(buffer);}
inline GLboolean glIsEnabled(GLenum cap){return _gl_loader_glisenabled(cap);}
inline GLboolean glIsEnabledi(GLenum target, GLuint index){return _gl_loader_glisenabledi(target, index);}
inline GLboolean glIsFramebuffer(GLuint framebuffer){return _gl_loader_glisframebuffer(framebuffer);}
inline GLboolean glIsList(GLuint list){return _gl_loader_glislist(list);}
inline GLboolean glIsProgram(GLuint program){return _gl_loader_glisprogram(program);}
inline GLboolean glIsProgramPipeline(GLuint pipeline){return _gl_loader_glisprogrampipeline(pipeline);}
inline GLboolean glIsQuery(GLuint id){return _gl_loader_glisquery(id);}
inline GLboolean glIsRenderbuffer(GLuint renderbuffer){return _gl_loader_glisrenderbuffer(renderbuffer);}
inline GLboolean glIsSampler(GLuint sampler){return _gl_loader_glissampler(sampler);}
inline GLboolean glIsShader(GLuint shader){return _gl_loader_glisshader(shader);}
inline GLboolean glIsSync(GLsync sync){return _gl_loader_glissync(sync);}
inline GLboolean glIsTexture(GLuint texture){return _gl_loader_glistexture(texture);}
inline GLboolean glIsTransformFeedback(GLuint id){return _gl_loader_glistransformfeedback(id);}
inline GLboolean glIsVertexArray(GLuint array){return _gl_loader_glisvertexarray(array);}
inline void glLightModelf(GLenum pname, GLfloat param){return _gl_loader_gllightmodelf(pname, param);}
inline void glLightModelfv(GLenum pname, const GLfloat * params){return _gl_loader_gllightmodelfv(pname, params);}
inline void glLightModeli(GLenum pname, GLint param){return _gl_loader_gllightmodeli(pname, param);}
inline void glLightModeliv(GLenum pname, const GLint * params){return _gl_loader_gllightmodeliv(pname, params);}
inline void glLightf(GLenum light, GLenum pname, GLfloat param){return _gl_loader_gllightf(light, pname, param);}
inline void glLightfv(GLenum light, GLenum pname, const GLfloat * params){return _gl_loader_gllightfv(light, pname, params);}
inline void glLighti(GLenum light, GLenum pname, GLint param){return _gl_loader_gllighti(light, pname, param);}
inline void glLightiv(GLenum light, GLenum pname, const GLint * params){return _gl_loader_gllightiv(light, pname, params);}
inline void glLineStipple(GLint factor, GLushort pattern){return _gl_loader_gllinestipple(factor, pattern);}
inline void glLineWidth(GLfloat width){return _gl_loader_gllinewidth(width);}
inline void glLinkProgram(GLuint program){return _gl_loader_gllinkprogram(program);}
inline void glListBase(GLuint base){return _gl_loader_gllistbase(base);}
inline void glLoadIdentity(){return _gl_loader_glloadidentity();}
inline void glLoadMatrixd(const GLdouble * m){return _gl_loader_glloadmatrixd(m);}
inline void glLoadMatrixf(const GLfloat * m){return _gl_loader_glloadmatrixf(m);}
inline void glLoadName(GLuint name){return _gl_loader_glloadname(name);}
inline void glLoadTransposeMatrixd(const GLdouble * m){return _gl_loader_glloadtransposematrixd(m);}
inline void glLoadTransposeMatrixf(const GLfloat * m){return _gl_loader_glloadtransposematrixf(m);}
inline void glLogicOp(GLenum opcode){return _gl_loader_gllogicop(opcode);}
inline void glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble * points){return _gl_loader_glmap1d(target, u1, u2, stride, order, points);}
inline void glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat * points){return _gl_loader_glmap1f(target, u1, u2, stride, order, points);}
inline void glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble * points){return _gl_loader_glmap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
inline void glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat * points){return _gl_loader_glmap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);}
inline void glMapBuffer(GLenum target, GLenum access){return _gl_loader_glmapbuffer(target, access);}
inline void glMapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access){return _gl_loader_glmapbufferrange(target, offset, length, access);}
inline void glMapGrid1d(GLint un, GLdouble u1, GLdouble u2){return _gl_loader_glmapgrid1d(un, u1, u2);}
inline void glMapGrid1f(GLint un, GLfloat u1, GLfloat u2){return _gl_loader_glmapgrid1f(un, u1, u2);}
inline void glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2){return _gl_loader_glmapgrid2d(un, u1, u2, vn, v1, v2);}
inline void glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2){return _gl_loader_glmapgrid2f(un, u1, u2, vn, v1, v2);}
inline void glMapNamedBuffer(GLuint buffer, GLenum access){return _gl_loader_glmapnamedbuffer(buffer, access);}
inline void glMapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access){return _gl_loader_glmapnamedbufferrange(buffer, offset, length, access);}
inline void glMaterialf(GLenum face, GLenum pname, GLfloat param){return _gl_loader_glmaterialf(face, pname, param);}
inline void glMaterialfv(GLenum face, GLenum pname, const GLfloat * params){return _gl_loader_glmaterialfv(face, pname, params);}
inline void glMateriali(GLenum face, GLenum pname, GLint param){return _gl_loader_glmateriali(face, pname, param);}
inline void glMaterialiv(GLenum face, GLenum pname, const GLint * params){return _gl_loader_glmaterialiv(face, pname, params);}
inline void glMatrixMode(GLenum mode){return _gl_loader_glmatrixmode(mode);}
inline void glMemoryBarrier(GLbitfield barriers){return _gl_loader_glmemorybarrier(barriers);}
inline void glMemoryBarrierByRegion(GLbitfield barriers){return _gl_loader_glmemorybarrierbyregion(barriers);}
inline void glMinSampleShading(GLfloat value){return _gl_loader_glminsampleshading(value);}
inline void glMultMatrixd(const GLdouble * m){return _gl_loader_glmultmatrixd(m);}
inline void glMultMatrixf(const GLfloat * m){return _gl_loader_glmultmatrixf(m);}
inline void glMultTransposeMatrixd(const GLdouble * m){return _gl_loader_glmulttransposematrixd(m);}
inline void glMultTransposeMatrixf(const GLfloat * m){return _gl_loader_glmulttransposematrixf(m);}
inline void glMultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount){return _gl_loader_glmultidrawarrays(mode, first, count, drawcount);}
inline void glMultiDrawArraysIndirect(GLenum mode, const void * indirect, GLsizei drawcount, GLsizei stride){return _gl_loader_glmultidrawarraysindirect(mode, indirect, drawcount, stride);}
inline void glMultiDrawArraysIndirectCount(GLenum mode, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){return _gl_loader_glmultidrawarraysindirectcount(mode, indirect, drawcount, maxdrawcount, stride);}
inline void glMultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const void * const * indices, GLsizei drawcount){return _gl_loader_glmultidrawelements(mode, count, type, indices, drawcount);}
inline void glMultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const void * const * indices, GLsizei drawcount, const GLint * basevertex){return _gl_loader_glmultidrawelementsbasevertex(mode, count, type, indices, drawcount, basevertex);}
inline void glMultiDrawElementsIndirect(GLenum mode, GLenum type, const void * indirect, GLsizei drawcount, GLsizei stride){return _gl_loader_glmultidrawelementsindirect(mode, type, indirect, drawcount, stride);}
inline void glMultiDrawElementsIndirectCount(GLenum mode, GLenum type, const void * indirect, GLintptr drawcount, GLsizei maxdrawcount, GLsizei stride){return _gl_loader_glmultidrawelementsindirectcount(mode, type, indirect, drawcount, maxdrawcount, stride);}
inline void glMultiTexCoord1d(GLenum target, GLdouble s){return _gl_loader_glmultitexcoord1d(target, s);}
inline void glMultiTexCoord1dv(GLenum target, const GLdouble * v){return _gl_loader_glmultitexcoord1dv(target, v);}
inline void glMultiTexCoord1f(GLenum target, GLfloat s){return _gl_loader_glmultitexcoord1f(target, s);}
inline void glMultiTexCoord1fv(GLenum target, const GLfloat * v){return _gl_loader_glmultitexcoord1fv(target, v);}
inline void glMultiTexCoord1i(GLenum target, GLint s){return _gl_loader_glmultitexcoord1i(target, s);}
inline void glMultiTexCoord1iv(GLenum target, const GLint * v){return _gl_loader_glmultitexcoord1iv(target, v);}
inline void glMultiTexCoord1s(GLenum target, GLshort s){return _gl_loader_glmultitexcoord1s(target, s);}
inline void glMultiTexCoord1sv(GLenum target, const GLshort * v){return _gl_loader_glmultitexcoord1sv(target, v);}
inline void glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t){return _gl_loader_glmultitexcoord2d(target, s, t);}
inline void glMultiTexCoord2dv(GLenum target, const GLdouble * v){return _gl_loader_glmultitexcoord2dv(target, v);}
inline void glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t){return _gl_loader_glmultitexcoord2f(target, s, t);}
inline void glMultiTexCoord2fv(GLenum target, const GLfloat * v){return _gl_loader_glmultitexcoord2fv(target, v);}
inline void glMultiTexCoord2i(GLenum target, GLint s, GLint t){return _gl_loader_glmultitexcoord2i(target, s, t);}
inline void glMultiTexCoord2iv(GLenum target, const GLint * v){return _gl_loader_glmultitexcoord2iv(target, v);}
inline void glMultiTexCoord2s(GLenum target, GLshort s, GLshort t){return _gl_loader_glmultitexcoord2s(target, s, t);}
inline void glMultiTexCoord2sv(GLenum target, const GLshort * v){return _gl_loader_glmultitexcoord2sv(target, v);}
inline void glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r){return _gl_loader_glmultitexcoord3d(target, s, t, r);}
inline void glMultiTexCoord3dv(GLenum target, const GLdouble * v){return _gl_loader_glmultitexcoord3dv(target, v);}
inline void glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r){return _gl_loader_glmultitexcoord3f(target, s, t, r);}
inline void glMultiTexCoord3fv(GLenum target, const GLfloat * v){return _gl_loader_glmultitexcoord3fv(target, v);}
inline void glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r){return _gl_loader_glmultitexcoord3i(target, s, t, r);}
inline void glMultiTexCoord3iv(GLenum target, const GLint * v){return _gl_loader_glmultitexcoord3iv(target, v);}
inline void glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r){return _gl_loader_glmultitexcoord3s(target, s, t, r);}
inline void glMultiTexCoord3sv(GLenum target, const GLshort * v){return _gl_loader_glmultitexcoord3sv(target, v);}
inline void glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q){return _gl_loader_glmultitexcoord4d(target, s, t, r, q);}
inline void glMultiTexCoord4dv(GLenum target, const GLdouble * v){return _gl_loader_glmultitexcoord4dv(target, v);}
inline void glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q){return _gl_loader_glmultitexcoord4f(target, s, t, r, q);}
inline void glMultiTexCoord4fv(GLenum target, const GLfloat * v){return _gl_loader_glmultitexcoord4fv(target, v);}
inline void glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q){return _gl_loader_glmultitexcoord4i(target, s, t, r, q);}
inline void glMultiTexCoord4iv(GLenum target, const GLint * v){return _gl_loader_glmultitexcoord4iv(target, v);}
inline void glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q){return _gl_loader_glmultitexcoord4s(target, s, t, r, q);}
inline void glMultiTexCoord4sv(GLenum target, const GLshort * v){return _gl_loader_glmultitexcoord4sv(target, v);}
inline void glMultiTexCoordP1ui(GLenum texture, GLenum type, GLuint coords){return _gl_loader_glmultitexcoordp1ui(texture, type, coords);}
inline void glMultiTexCoordP1uiv(GLenum texture, GLenum type, const GLuint * coords){return _gl_loader_glmultitexcoordp1uiv(texture, type, coords);}
inline void glMultiTexCoordP2ui(GLenum texture, GLenum type, GLuint coords){return _gl_loader_glmultitexcoordp2ui(texture, type, coords);}
inline void glMultiTexCoordP2uiv(GLenum texture, GLenum type, const GLuint * coords){return _gl_loader_glmultitexcoordp2uiv(texture, type, coords);}
inline void glMultiTexCoordP3ui(GLenum texture, GLenum type, GLuint coords){return _gl_loader_glmultitexcoordp3ui(texture, type, coords);}
inline void glMultiTexCoordP3uiv(GLenum texture, GLenum type, const GLuint * coords){return _gl_loader_glmultitexcoordp3uiv(texture, type, coords);}
inline void glMultiTexCoordP4ui(GLenum texture, GLenum type, GLuint coords){return _gl_loader_glmultitexcoordp4ui(texture, type, coords);}
inline void glMultiTexCoordP4uiv(GLenum texture, GLenum type, const GLuint * coords){return _gl_loader_glmultitexcoordp4uiv(texture, type, coords);}
inline void glNamedBufferData(GLuint buffer, GLsizeiptr size, const void * data, GLenum usage){return _gl_loader_glnamedbufferdata(buffer, size, data, usage);}
inline void glNamedBufferStorage(GLuint buffer, GLsizeiptr size, const void * data, GLbitfield flags){return _gl_loader_glnamedbufferstorage(buffer, size, data, flags);}
inline void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void * data){return _gl_loader_glnamedbuffersubdata(buffer, offset, size, data);}
inline void glNamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf){return _gl_loader_glnamedframebufferdrawbuffer(framebuffer, buf);}
inline void glNamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs){return _gl_loader_glnamedframebufferdrawbuffers(framebuffer, n, bufs);}
inline void glNamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param){return _gl_loader_glnamedframebufferparameteri(framebuffer, pname, param);}
inline void glNamedFramebufferReadBuffer(GLuint framebuffer, GLenum src){return _gl_loader_glnamedframebufferreadbuffer(framebuffer, src);}
inline void glNamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer){return _gl_loader_glnamedframebufferrenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);}
inline void glNamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level){return _gl_loader_glnamedframebuffertexture(framebuffer, attachment, texture, level);}
inline void glNamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer){return _gl_loader_glnamedframebuffertexturelayer(framebuffer, attachment, texture, level, layer);}
inline void glNamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_glnamedrenderbufferstorage(renderbuffer, internalformat, width, height);}
inline void glNamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_glnamedrenderbufferstoragemultisample(renderbuffer, samples, internalformat, width, height);}
inline void glNewList(GLuint list, GLenum mode){return _gl_loader_glnewlist(list, mode);}
inline void glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz){return _gl_loader_glnormal3b(nx, ny, nz);}
inline void glNormal3bv(const GLbyte * v){return _gl_loader_glnormal3bv(v);}
inline void glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz){return _gl_loader_glnormal3d(nx, ny, nz);}
inline void glNormal3dv(const GLdouble * v){return _gl_loader_glnormal3dv(v);}
inline void glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz){return _gl_loader_glnormal3f(nx, ny, nz);}
inline void glNormal3fv(const GLfloat * v){return _gl_loader_glnormal3fv(v);}
inline void glNormal3i(GLint nx, GLint ny, GLint nz){return _gl_loader_glnormal3i(nx, ny, nz);}
inline void glNormal3iv(const GLint * v){return _gl_loader_glnormal3iv(v);}
inline void glNormal3s(GLshort nx, GLshort ny, GLshort nz){return _gl_loader_glnormal3s(nx, ny, nz);}
inline void glNormal3sv(const GLshort * v){return _gl_loader_glnormal3sv(v);}
inline void glNormalP3ui(GLenum type, GLuint coords){return _gl_loader_glnormalp3ui(type, coords);}
inline void glNormalP3uiv(GLenum type, const GLuint * coords){return _gl_loader_glnormalp3uiv(type, coords);}
inline void glNormalPointer(GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glnormalpointer(type, stride, pointer);}
inline void glObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label){return _gl_loader_globjectlabel(identifier, name, length, label);}
inline void glObjectPtrLabel(const void * ptr, GLsizei length, const GLchar * label){return _gl_loader_globjectptrlabel(ptr, length, label);}
inline void glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar){return _gl_loader_glortho(left, right, bottom, top, zNear, zFar);}
inline void glPassThrough(GLfloat token){return _gl_loader_glpassthrough(token);}
inline void glPatchParameterfv(GLenum pname, const GLfloat * values){return _gl_loader_glpatchparameterfv(pname, values);}
inline void glPatchParameteri(GLenum pname, GLint value){return _gl_loader_glpatchparameteri(pname, value);}
inline void glPauseTransformFeedback(){return _gl_loader_glpausetransformfeedback();}
inline void glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat * values){return _gl_loader_glpixelmapfv(map, mapsize, values);}
inline void glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint * values){return _gl_loader_glpixelmapuiv(map, mapsize, values);}
inline void glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort * values){return _gl_loader_glpixelmapusv(map, mapsize, values);}
inline void glPixelStoref(GLenum pname, GLfloat param){return _gl_loader_glpixelstoref(pname, param);}
inline void glPixelStorei(GLenum pname, GLint param){return _gl_loader_glpixelstorei(pname, param);}
inline void glPixelTransferf(GLenum pname, GLfloat param){return _gl_loader_glpixeltransferf(pname, param);}
inline void glPixelTransferi(GLenum pname, GLint param){return _gl_loader_glpixeltransferi(pname, param);}
inline void glPixelZoom(GLfloat xfactor, GLfloat yfactor){return _gl_loader_glpixelzoom(xfactor, yfactor);}
inline void glPointParameterf(GLenum pname, GLfloat param){return _gl_loader_glpointparameterf(pname, param);}
inline void glPointParameterfv(GLenum pname, const GLfloat * params){return _gl_loader_glpointparameterfv(pname, params);}
inline void glPointParameteri(GLenum pname, GLint param){return _gl_loader_glpointparameteri(pname, param);}
inline void glPointParameteriv(GLenum pname, const GLint * params){return _gl_loader_glpointparameteriv(pname, params);}
inline void glPointSize(GLfloat size){return _gl_loader_glpointsize(size);}
inline void glPolygonMode(GLenum face, GLenum mode){return _gl_loader_glpolygonmode(face, mode);}
inline void glPolygonOffset(GLfloat factor, GLfloat units){return _gl_loader_glpolygonoffset(factor, units);}
inline void glPolygonOffsetClamp(GLfloat factor, GLfloat units, GLfloat clamp){return _gl_loader_glpolygonoffsetclamp(factor, units, clamp);}
inline void glPolygonStipple(const GLubyte * mask){return _gl_loader_glpolygonstipple(mask);}
inline void glPopAttrib(){return _gl_loader_glpopattrib();}
inline void glPopClientAttrib(){return _gl_loader_glpopclientattrib();}
inline void glPopDebugGroup(){return _gl_loader_glpopdebuggroup();}
inline void glPopMatrix(){return _gl_loader_glpopmatrix();}
inline void glPopName(){return _gl_loader_glpopname();}
inline void glPrimitiveRestartIndex(GLuint index){return _gl_loader_glprimitiverestartindex(index);}
inline void glPrioritizeTextures(GLsizei n, const GLuint * textures, const GLfloat * priorities){return _gl_loader_glprioritizetextures(n, textures, priorities);}
inline void glProgramBinary(GLuint program, GLenum binaryFormat, const void * binary, GLsizei length){return _gl_loader_glprogrambinary(program, binaryFormat, binary, length);}
inline void glProgramParameteri(GLuint program, GLenum pname, GLint value){return _gl_loader_glprogramparameteri(program, pname, value);}
inline void glProgramUniform1d(GLuint program, GLint location, GLdouble v0){return _gl_loader_glprogramuniform1d(program, location, v0);}
inline void glProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){return _gl_loader_glprogramuniform1dv(program, location, count, value);}
inline void glProgramUniform1f(GLuint program, GLint location, GLfloat v0){return _gl_loader_glprogramuniform1f(program, location, v0);}
inline void glProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){return _gl_loader_glprogramuniform1fv(program, location, count, value);}
inline void glProgramUniform1i(GLuint program, GLint location, GLint v0){return _gl_loader_glprogramuniform1i(program, location, v0);}
inline void glProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value){return _gl_loader_glprogramuniform1iv(program, location, count, value);}
inline void glProgramUniform1ui(GLuint program, GLint location, GLuint v0){return _gl_loader_glprogramuniform1ui(program, location, v0);}
inline void glProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){return _gl_loader_glprogramuniform1uiv(program, location, count, value);}
inline void glProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1){return _gl_loader_glprogramuniform2d(program, location, v0, v1);}
inline void glProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){return _gl_loader_glprogramuniform2dv(program, location, count, value);}
inline void glProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1){return _gl_loader_glprogramuniform2f(program, location, v0, v1);}
inline void glProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){return _gl_loader_glprogramuniform2fv(program, location, count, value);}
inline void glProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1){return _gl_loader_glprogramuniform2i(program, location, v0, v1);}
inline void glProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value){return _gl_loader_glprogramuniform2iv(program, location, count, value);}
inline void glProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1){return _gl_loader_glprogramuniform2ui(program, location, v0, v1);}
inline void glProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){return _gl_loader_glprogramuniform2uiv(program, location, count, value);}
inline void glProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2){return _gl_loader_glprogramuniform3d(program, location, v0, v1, v2);}
inline void glProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){return _gl_loader_glprogramuniform3dv(program, location, count, value);}
inline void glProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2){return _gl_loader_glprogramuniform3f(program, location, v0, v1, v2);}
inline void glProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){return _gl_loader_glprogramuniform3fv(program, location, count, value);}
inline void glProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2){return _gl_loader_glprogramuniform3i(program, location, v0, v1, v2);}
inline void glProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value){return _gl_loader_glprogramuniform3iv(program, location, count, value);}
inline void glProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2){return _gl_loader_glprogramuniform3ui(program, location, v0, v1, v2);}
inline void glProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){return _gl_loader_glprogramuniform3uiv(program, location, count, value);}
inline void glProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3){return _gl_loader_glprogramuniform4d(program, location, v0, v1, v2, v3);}
inline void glProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value){return _gl_loader_glprogramuniform4dv(program, location, count, value);}
inline void glProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){return _gl_loader_glprogramuniform4f(program, location, v0, v1, v2, v3);}
inline void glProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value){return _gl_loader_glprogramuniform4fv(program, location, count, value);}
inline void glProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3){return _gl_loader_glprogramuniform4i(program, location, v0, v1, v2, v3);}
inline void glProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value){return _gl_loader_glprogramuniform4iv(program, location, count, value);}
inline void glProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){return _gl_loader_glprogramuniform4ui(program, location, v0, v1, v2, v3);}
inline void glProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value){return _gl_loader_glprogramuniform4uiv(program, location, count, value);}
inline void glProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix2dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix2fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix2x3dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix2x3fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix2x4dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix2x4fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix3dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix3fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix3x2dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix3x2fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix3x4dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix3x4fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix4dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix4fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix4x2dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix4x2fv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_glprogramuniformmatrix4x3dv(program, location, count, transpose, value);}
inline void glProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_glprogramuniformmatrix4x3fv(program, location, count, transpose, value);}
inline void glProvokingVertex(GLenum mode){return _gl_loader_glprovokingvertex(mode);}
inline void glPushAttrib(GLbitfield mask){return _gl_loader_glpushattrib(mask);}
inline void glPushClientAttrib(GLbitfield mask){return _gl_loader_glpushclientattrib(mask);}
inline void glPushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message){return _gl_loader_glpushdebuggroup(source, id, length, message);}
inline void glPushMatrix(){return _gl_loader_glpushmatrix();}
inline void glPushName(GLuint name){return _gl_loader_glpushname(name);}
inline void glQueryCounter(GLuint id, GLenum target){return _gl_loader_glquerycounter(id, target);}
inline void glRasterPos2d(GLdouble x, GLdouble y){return _gl_loader_glrasterpos2d(x, y);}
inline void glRasterPos2dv(const GLdouble * v){return _gl_loader_glrasterpos2dv(v);}
inline void glRasterPos2f(GLfloat x, GLfloat y){return _gl_loader_glrasterpos2f(x, y);}
inline void glRasterPos2fv(const GLfloat * v){return _gl_loader_glrasterpos2fv(v);}
inline void glRasterPos2i(GLint x, GLint y){return _gl_loader_glrasterpos2i(x, y);}
inline void glRasterPos2iv(const GLint * v){return _gl_loader_glrasterpos2iv(v);}
inline void glRasterPos2s(GLshort x, GLshort y){return _gl_loader_glrasterpos2s(x, y);}
inline void glRasterPos2sv(const GLshort * v){return _gl_loader_glrasterpos2sv(v);}
inline void glRasterPos3d(GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glrasterpos3d(x, y, z);}
inline void glRasterPos3dv(const GLdouble * v){return _gl_loader_glrasterpos3dv(v);}
inline void glRasterPos3f(GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glrasterpos3f(x, y, z);}
inline void glRasterPos3fv(const GLfloat * v){return _gl_loader_glrasterpos3fv(v);}
inline void glRasterPos3i(GLint x, GLint y, GLint z){return _gl_loader_glrasterpos3i(x, y, z);}
inline void glRasterPos3iv(const GLint * v){return _gl_loader_glrasterpos3iv(v);}
inline void glRasterPos3s(GLshort x, GLshort y, GLshort z){return _gl_loader_glrasterpos3s(x, y, z);}
inline void glRasterPos3sv(const GLshort * v){return _gl_loader_glrasterpos3sv(v);}
inline void glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){return _gl_loader_glrasterpos4d(x, y, z, w);}
inline void glRasterPos4dv(const GLdouble * v){return _gl_loader_glrasterpos4dv(v);}
inline void glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){return _gl_loader_glrasterpos4f(x, y, z, w);}
inline void glRasterPos4fv(const GLfloat * v){return _gl_loader_glrasterpos4fv(v);}
inline void glRasterPos4i(GLint x, GLint y, GLint z, GLint w){return _gl_loader_glrasterpos4i(x, y, z, w);}
inline void glRasterPos4iv(const GLint * v){return _gl_loader_glrasterpos4iv(v);}
inline void glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w){return _gl_loader_glrasterpos4s(x, y, z, w);}
inline void glRasterPos4sv(const GLshort * v){return _gl_loader_glrasterpos4sv(v);}
inline void glReadBuffer(GLenum src){return _gl_loader_glreadbuffer(src);}
inline void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels){return _gl_loader_glreadpixels(x, y, width, height, format, type, pixels);}
inline void glReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void * data){return _gl_loader_glreadnpixels(x, y, width, height, format, type, bufSize, data);}
inline void glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2){return _gl_loader_glrectd(x1, y1, x2, y2);}
inline void glRectdv(const GLdouble * v1, const GLdouble * v2){return _gl_loader_glrectdv(v1, v2);}
inline void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2){return _gl_loader_glrectf(x1, y1, x2, y2);}
inline void glRectfv(const GLfloat * v1, const GLfloat * v2){return _gl_loader_glrectfv(v1, v2);}
inline void glRecti(GLint x1, GLint y1, GLint x2, GLint y2){return _gl_loader_glrecti(x1, y1, x2, y2);}
inline void glRectiv(const GLint * v1, const GLint * v2){return _gl_loader_glrectiv(v1, v2);}
inline void glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2){return _gl_loader_glrects(x1, y1, x2, y2);}
inline void glRectsv(const GLshort * v1, const GLshort * v2){return _gl_loader_glrectsv(v1, v2);}
inline void glReleaseShaderCompiler(){return _gl_loader_glreleaseshadercompiler();}
inline GLint glRenderMode(GLenum mode){return _gl_loader_glrendermode(mode);}
inline void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_glrenderbufferstorage(target, internalformat, width, height);}
inline void glRenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_glrenderbufferstoragemultisample(target, samples, internalformat, width, height);}
inline void glResumeTransformFeedback(){return _gl_loader_glresumetransformfeedback();}
inline void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glrotated(angle, x, y, z);}
inline void glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glrotatef(angle, x, y, z);}
inline void glSampleCoverage(GLfloat value, GLboolean invert){return _gl_loader_glsamplecoverage(value, invert);}
inline void glSampleMaski(GLuint maskNumber, GLbitfield mask){return _gl_loader_glsamplemaski(maskNumber, mask);}
inline void glSamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param){return _gl_loader_glsamplerparameteriiv(sampler, pname, param);}
inline void glSamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param){return _gl_loader_glsamplerparameteriuiv(sampler, pname, param);}
inline void glSamplerParameterf(GLuint sampler, GLenum pname, GLfloat param){return _gl_loader_glsamplerparameterf(sampler, pname, param);}
inline void glSamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param){return _gl_loader_glsamplerparameterfv(sampler, pname, param);}
inline void glSamplerParameteri(GLuint sampler, GLenum pname, GLint param){return _gl_loader_glsamplerparameteri(sampler, pname, param);}
inline void glSamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param){return _gl_loader_glsamplerparameteriv(sampler, pname, param);}
inline void glScaled(GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glscaled(x, y, z);}
inline void glScalef(GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glscalef(x, y, z);}
inline void glScissor(GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glscissor(x, y, width, height);}
inline void glScissorArrayv(GLuint first, GLsizei count, const GLint * v){return _gl_loader_glscissorarrayv(first, count, v);}
inline void glScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height){return _gl_loader_glscissorindexed(index, left, bottom, width, height);}
inline void glScissorIndexedv(GLuint index, const GLint * v){return _gl_loader_glscissorindexedv(index, v);}
inline void glSecondaryColor3b(GLbyte red, GLbyte green, GLbyte blue){return _gl_loader_glsecondarycolor3b(red, green, blue);}
inline void glSecondaryColor3bv(const GLbyte * v){return _gl_loader_glsecondarycolor3bv(v);}
inline void glSecondaryColor3d(GLdouble red, GLdouble green, GLdouble blue){return _gl_loader_glsecondarycolor3d(red, green, blue);}
inline void glSecondaryColor3dv(const GLdouble * v){return _gl_loader_glsecondarycolor3dv(v);}
inline void glSecondaryColor3f(GLfloat red, GLfloat green, GLfloat blue){return _gl_loader_glsecondarycolor3f(red, green, blue);}
inline void glSecondaryColor3fv(const GLfloat * v){return _gl_loader_glsecondarycolor3fv(v);}
inline void glSecondaryColor3i(GLint red, GLint green, GLint blue){return _gl_loader_glsecondarycolor3i(red, green, blue);}
inline void glSecondaryColor3iv(const GLint * v){return _gl_loader_glsecondarycolor3iv(v);}
inline void glSecondaryColor3s(GLshort red, GLshort green, GLshort blue){return _gl_loader_glsecondarycolor3s(red, green, blue);}
inline void glSecondaryColor3sv(const GLshort * v){return _gl_loader_glsecondarycolor3sv(v);}
inline void glSecondaryColor3ub(GLubyte red, GLubyte green, GLubyte blue){return _gl_loader_glsecondarycolor3ub(red, green, blue);}
inline void glSecondaryColor3ubv(const GLubyte * v){return _gl_loader_glsecondarycolor3ubv(v);}
inline void glSecondaryColor3ui(GLuint red, GLuint green, GLuint blue){return _gl_loader_glsecondarycolor3ui(red, green, blue);}
inline void glSecondaryColor3uiv(const GLuint * v){return _gl_loader_glsecondarycolor3uiv(v);}
inline void glSecondaryColor3us(GLushort red, GLushort green, GLushort blue){return _gl_loader_glsecondarycolor3us(red, green, blue);}
inline void glSecondaryColor3usv(const GLushort * v){return _gl_loader_glsecondarycolor3usv(v);}
inline void glSecondaryColorP3ui(GLenum type, GLuint color){return _gl_loader_glsecondarycolorp3ui(type, color);}
inline void glSecondaryColorP3uiv(GLenum type, const GLuint * color){return _gl_loader_glsecondarycolorp3uiv(type, color);}
inline void glSecondaryColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glsecondarycolorpointer(size, type, stride, pointer);}
inline void glSelectBuffer(GLsizei size, GLuint * buffer){return _gl_loader_glselectbuffer(size, buffer);}
inline void glShadeModel(GLenum mode){return _gl_loader_glshademodel(mode);}
inline void glShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryFormat, const void * binary, GLsizei length){return _gl_loader_glshaderbinary(count, shaders, binaryFormat, binary, length);}
inline void glShaderSource(GLuint shader, GLsizei count, const GLchar * const * string, const GLint * length){return _gl_loader_glshadersource(shader, count, string, length);}
inline void glShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding){return _gl_loader_glshaderstorageblockbinding(program, storageBlockIndex, storageBlockBinding);}
inline void glSpecializeShader(GLuint shader, const GLchar * pEntryPoint, GLuint numSpecializationConstants, const GLuint * pConstantIndex, const GLuint * pConstantValue){return _gl_loader_glspecializeshader(shader, pEntryPoint, numSpecializationConstants, pConstantIndex, pConstantValue);}
inline void glStencilFunc(GLenum func, GLint ref, GLuint mask){return _gl_loader_glstencilfunc(func, ref, mask);}
inline void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask){return _gl_loader_glstencilfuncseparate(face, func, ref, mask);}
inline void glStencilMask(GLuint mask){return _gl_loader_glstencilmask(mask);}
inline void glStencilMaskSeparate(GLenum face, GLuint mask){return _gl_loader_glstencilmaskseparate(face, mask);}
inline void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass){return _gl_loader_glstencilop(fail, zfail, zpass);}
inline void glStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass){return _gl_loader_glstencilopseparate(face, sfail, dpfail, dppass);}
inline void glTexBuffer(GLenum target, GLenum internalformat, GLuint buffer){return _gl_loader_gltexbuffer(target, internalformat, buffer);}
inline void glTexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){return _gl_loader_gltexbufferrange(target, internalformat, buffer, offset, size);}
inline void glTexCoord1d(GLdouble s){return _gl_loader_gltexcoord1d(s);}
inline void glTexCoord1dv(const GLdouble * v){return _gl_loader_gltexcoord1dv(v);}
inline void glTexCoord1f(GLfloat s){return _gl_loader_gltexcoord1f(s);}
inline void glTexCoord1fv(const GLfloat * v){return _gl_loader_gltexcoord1fv(v);}
inline void glTexCoord1i(GLint s){return _gl_loader_gltexcoord1i(s);}
inline void glTexCoord1iv(const GLint * v){return _gl_loader_gltexcoord1iv(v);}
inline void glTexCoord1s(GLshort s){return _gl_loader_gltexcoord1s(s);}
inline void glTexCoord1sv(const GLshort * v){return _gl_loader_gltexcoord1sv(v);}
inline void glTexCoord2d(GLdouble s, GLdouble t){return _gl_loader_gltexcoord2d(s, t);}
inline void glTexCoord2dv(const GLdouble * v){return _gl_loader_gltexcoord2dv(v);}
inline void glTexCoord2f(GLfloat s, GLfloat t){return _gl_loader_gltexcoord2f(s, t);}
inline void glTexCoord2fv(const GLfloat * v){return _gl_loader_gltexcoord2fv(v);}
inline void glTexCoord2i(GLint s, GLint t){return _gl_loader_gltexcoord2i(s, t);}
inline void glTexCoord2iv(const GLint * v){return _gl_loader_gltexcoord2iv(v);}
inline void glTexCoord2s(GLshort s, GLshort t){return _gl_loader_gltexcoord2s(s, t);}
inline void glTexCoord2sv(const GLshort * v){return _gl_loader_gltexcoord2sv(v);}
inline void glTexCoord3d(GLdouble s, GLdouble t, GLdouble r){return _gl_loader_gltexcoord3d(s, t, r);}
inline void glTexCoord3dv(const GLdouble * v){return _gl_loader_gltexcoord3dv(v);}
inline void glTexCoord3f(GLfloat s, GLfloat t, GLfloat r){return _gl_loader_gltexcoord3f(s, t, r);}
inline void glTexCoord3fv(const GLfloat * v){return _gl_loader_gltexcoord3fv(v);}
inline void glTexCoord3i(GLint s, GLint t, GLint r){return _gl_loader_gltexcoord3i(s, t, r);}
inline void glTexCoord3iv(const GLint * v){return _gl_loader_gltexcoord3iv(v);}
inline void glTexCoord3s(GLshort s, GLshort t, GLshort r){return _gl_loader_gltexcoord3s(s, t, r);}
inline void glTexCoord3sv(const GLshort * v){return _gl_loader_gltexcoord3sv(v);}
inline void glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q){return _gl_loader_gltexcoord4d(s, t, r, q);}
inline void glTexCoord4dv(const GLdouble * v){return _gl_loader_gltexcoord4dv(v);}
inline void glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q){return _gl_loader_gltexcoord4f(s, t, r, q);}
inline void glTexCoord4fv(const GLfloat * v){return _gl_loader_gltexcoord4fv(v);}
inline void glTexCoord4i(GLint s, GLint t, GLint r, GLint q){return _gl_loader_gltexcoord4i(s, t, r, q);}
inline void glTexCoord4iv(const GLint * v){return _gl_loader_gltexcoord4iv(v);}
inline void glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q){return _gl_loader_gltexcoord4s(s, t, r, q);}
inline void glTexCoord4sv(const GLshort * v){return _gl_loader_gltexcoord4sv(v);}
inline void glTexCoordP1ui(GLenum type, GLuint coords){return _gl_loader_gltexcoordp1ui(type, coords);}
inline void glTexCoordP1uiv(GLenum type, const GLuint * coords){return _gl_loader_gltexcoordp1uiv(type, coords);}
inline void glTexCoordP2ui(GLenum type, GLuint coords){return _gl_loader_gltexcoordp2ui(type, coords);}
inline void glTexCoordP2uiv(GLenum type, const GLuint * coords){return _gl_loader_gltexcoordp2uiv(type, coords);}
inline void glTexCoordP3ui(GLenum type, GLuint coords){return _gl_loader_gltexcoordp3ui(type, coords);}
inline void glTexCoordP3uiv(GLenum type, const GLuint * coords){return _gl_loader_gltexcoordp3uiv(type, coords);}
inline void glTexCoordP4ui(GLenum type, GLuint coords){return _gl_loader_gltexcoordp4ui(type, coords);}
inline void glTexCoordP4uiv(GLenum type, const GLuint * coords){return _gl_loader_gltexcoordp4uiv(type, coords);}
inline void glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_gltexcoordpointer(size, type, stride, pointer);}
inline void glTexEnvf(GLenum target, GLenum pname, GLfloat param){return _gl_loader_gltexenvf(target, pname, param);}
inline void glTexEnvfv(GLenum target, GLenum pname, const GLfloat * params){return _gl_loader_gltexenvfv(target, pname, params);}
inline void glTexEnvi(GLenum target, GLenum pname, GLint param){return _gl_loader_gltexenvi(target, pname, param);}
inline void glTexEnviv(GLenum target, GLenum pname, const GLint * params){return _gl_loader_gltexenviv(target, pname, params);}
inline void glTexGend(GLenum coord, GLenum pname, GLdouble param){return _gl_loader_gltexgend(coord, pname, param);}
inline void glTexGendv(GLenum coord, GLenum pname, const GLdouble * params){return _gl_loader_gltexgendv(coord, pname, params);}
inline void glTexGenf(GLenum coord, GLenum pname, GLfloat param){return _gl_loader_gltexgenf(coord, pname, param);}
inline void glTexGenfv(GLenum coord, GLenum pname, const GLfloat * params){return _gl_loader_gltexgenfv(coord, pname, params);}
inline void glTexGeni(GLenum coord, GLenum pname, GLint param){return _gl_loader_gltexgeni(coord, pname, param);}
inline void glTexGeniv(GLenum coord, GLenum pname, const GLint * params){return _gl_loader_gltexgeniv(coord, pname, params);}
inline void glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void * pixels){return _gl_loader_glteximage1d(target, level, internalformat, width, border, format, type, pixels);}
inline void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels){return _gl_loader_glteximage2d(target, level, internalformat, width, height, border, format, type, pixels);}
inline void glTexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){return _gl_loader_glteximage2dmultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
inline void glTexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void * pixels){return _gl_loader_glteximage3d(target, level, internalformat, width, height, depth, border, format, type, pixels);}
inline void glTexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){return _gl_loader_glteximage3dmultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
inline void glTexParameterIiv(GLenum target, GLenum pname, const GLint * params){return _gl_loader_gltexparameteriiv(target, pname, params);}
inline void glTexParameterIuiv(GLenum target, GLenum pname, const GLuint * params){return _gl_loader_gltexparameteriuiv(target, pname, params);}
inline void glTexParameterf(GLenum target, GLenum pname, GLfloat param){return _gl_loader_gltexparameterf(target, pname, param);}
inline void glTexParameterfv(GLenum target, GLenum pname, const GLfloat * params){return _gl_loader_gltexparameterfv(target, pname, params);}
inline void glTexParameteri(GLenum target, GLenum pname, GLint param){return _gl_loader_gltexparameteri(target, pname, param);}
inline void glTexParameteriv(GLenum target, GLenum pname, const GLint * params){return _gl_loader_gltexparameteriv(target, pname, params);}
inline void glTexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width){return _gl_loader_gltexstorage1d(target, levels, internalformat, width);}
inline void glTexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_gltexstorage2d(target, levels, internalformat, width, height);}
inline void glTexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){return _gl_loader_gltexstorage2dmultisample(target, samples, internalformat, width, height, fixedsamplelocations);}
inline void glTexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){return _gl_loader_gltexstorage3d(target, levels, internalformat, width, height, depth);}
inline void glTexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){return _gl_loader_gltexstorage3dmultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);}
inline void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexsubimage1d(target, level, xoffset, width, format, type, pixels);}
inline void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexsubimage2d(target, level, xoffset, yoffset, width, height, format, type, pixels);}
inline void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexsubimage3d(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
inline void glTextureBarrier(){return _gl_loader_gltexturebarrier();}
inline void glTextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer){return _gl_loader_gltexturebuffer(texture, internalformat, buffer);}
inline void glTextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size){return _gl_loader_gltexturebufferrange(texture, internalformat, buffer, offset, size);}
inline void glTextureParameterIiv(GLuint texture, GLenum pname, const GLint * params){return _gl_loader_gltextureparameteriiv(texture, pname, params);}
inline void glTextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params){return _gl_loader_gltextureparameteriuiv(texture, pname, params);}
inline void glTextureParameterf(GLuint texture, GLenum pname, GLfloat param){return _gl_loader_gltextureparameterf(texture, pname, param);}
inline void glTextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param){return _gl_loader_gltextureparameterfv(texture, pname, param);}
inline void glTextureParameteri(GLuint texture, GLenum pname, GLint param){return _gl_loader_gltextureparameteri(texture, pname, param);}
inline void glTextureParameteriv(GLuint texture, GLenum pname, const GLint * param){return _gl_loader_gltextureparameteriv(texture, pname, param);}
inline void glTextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width){return _gl_loader_gltexturestorage1d(texture, levels, internalformat, width);}
inline void glTextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height){return _gl_loader_gltexturestorage2d(texture, levels, internalformat, width, height);}
inline void glTextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations){return _gl_loader_gltexturestorage2dmultisample(texture, samples, internalformat, width, height, fixedsamplelocations);}
inline void glTextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth){return _gl_loader_gltexturestorage3d(texture, levels, internalformat, width, height, depth);}
inline void glTextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations){return _gl_loader_gltexturestorage3dmultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);}
inline void glTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexturesubimage1d(texture, level, xoffset, width, format, type, pixels);}
inline void glTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexturesubimage2d(texture, level, xoffset, yoffset, width, height, format, type, pixels);}
inline void glTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const void * pixels){return _gl_loader_gltexturesubimage3d(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);}
inline void glTextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers){return _gl_loader_gltextureview(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);}
inline void glTransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer){return _gl_loader_gltransformfeedbackbufferbase(xfb, index, buffer);}
inline void glTransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size){return _gl_loader_gltransformfeedbackbufferrange(xfb, index, buffer, offset, size);}
inline void glTransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar * const * varyings, GLenum bufferMode){return _gl_loader_gltransformfeedbackvaryings(program, count, varyings, bufferMode);}
inline void glTranslated(GLdouble x, GLdouble y, GLdouble z){return _gl_loader_gltranslated(x, y, z);}
inline void glTranslatef(GLfloat x, GLfloat y, GLfloat z){return _gl_loader_gltranslatef(x, y, z);}
inline void glUniform1d(GLint location, GLdouble x){return _gl_loader_gluniform1d(location, x);}
inline void glUniform1dv(GLint location, GLsizei count, const GLdouble * value){return _gl_loader_gluniform1dv(location, count, value);}
inline void glUniform1f(GLint location, GLfloat v0){return _gl_loader_gluniform1f(location, v0);}
inline void glUniform1fv(GLint location, GLsizei count, const GLfloat * value){return _gl_loader_gluniform1fv(location, count, value);}
inline void glUniform1i(GLint location, GLint v0){return _gl_loader_gluniform1i(location, v0);}
inline void glUniform1iv(GLint location, GLsizei count, const GLint * value){return _gl_loader_gluniform1iv(location, count, value);}
inline void glUniform1ui(GLint location, GLuint v0){return _gl_loader_gluniform1ui(location, v0);}
inline void glUniform1uiv(GLint location, GLsizei count, const GLuint * value){return _gl_loader_gluniform1uiv(location, count, value);}
inline void glUniform2d(GLint location, GLdouble x, GLdouble y){return _gl_loader_gluniform2d(location, x, y);}
inline void glUniform2dv(GLint location, GLsizei count, const GLdouble * value){return _gl_loader_gluniform2dv(location, count, value);}
inline void glUniform2f(GLint location, GLfloat v0, GLfloat v1){return _gl_loader_gluniform2f(location, v0, v1);}
inline void glUniform2fv(GLint location, GLsizei count, const GLfloat * value){return _gl_loader_gluniform2fv(location, count, value);}
inline void glUniform2i(GLint location, GLint v0, GLint v1){return _gl_loader_gluniform2i(location, v0, v1);}
inline void glUniform2iv(GLint location, GLsizei count, const GLint * value){return _gl_loader_gluniform2iv(location, count, value);}
inline void glUniform2ui(GLint location, GLuint v0, GLuint v1){return _gl_loader_gluniform2ui(location, v0, v1);}
inline void glUniform2uiv(GLint location, GLsizei count, const GLuint * value){return _gl_loader_gluniform2uiv(location, count, value);}
inline void glUniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z){return _gl_loader_gluniform3d(location, x, y, z);}
inline void glUniform3dv(GLint location, GLsizei count, const GLdouble * value){return _gl_loader_gluniform3dv(location, count, value);}
inline void glUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2){return _gl_loader_gluniform3f(location, v0, v1, v2);}
inline void glUniform3fv(GLint location, GLsizei count, const GLfloat * value){return _gl_loader_gluniform3fv(location, count, value);}
inline void glUniform3i(GLint location, GLint v0, GLint v1, GLint v2){return _gl_loader_gluniform3i(location, v0, v1, v2);}
inline void glUniform3iv(GLint location, GLsizei count, const GLint * value){return _gl_loader_gluniform3iv(location, count, value);}
inline void glUniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2){return _gl_loader_gluniform3ui(location, v0, v1, v2);}
inline void glUniform3uiv(GLint location, GLsizei count, const GLuint * value){return _gl_loader_gluniform3uiv(location, count, value);}
inline void glUniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w){return _gl_loader_gluniform4d(location, x, y, z, w);}
inline void glUniform4dv(GLint location, GLsizei count, const GLdouble * value){return _gl_loader_gluniform4dv(location, count, value);}
inline void glUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){return _gl_loader_gluniform4f(location, v0, v1, v2, v3);}
inline void glUniform4fv(GLint location, GLsizei count, const GLfloat * value){return _gl_loader_gluniform4fv(location, count, value);}
inline void glUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3){return _gl_loader_gluniform4i(location, v0, v1, v2, v3);}
inline void glUniform4iv(GLint location, GLsizei count, const GLint * value){return _gl_loader_gluniform4iv(location, count, value);}
inline void glUniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3){return _gl_loader_gluniform4ui(location, v0, v1, v2, v3);}
inline void glUniform4uiv(GLint location, GLsizei count, const GLuint * value){return _gl_loader_gluniform4uiv(location, count, value);}
inline void glUniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding){return _gl_loader_gluniformblockbinding(program, uniformBlockIndex, uniformBlockBinding);}
inline void glUniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix2dv(location, count, transpose, value);}
inline void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix2fv(location, count, transpose, value);}
inline void glUniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix2x3dv(location, count, transpose, value);}
inline void glUniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix2x3fv(location, count, transpose, value);}
inline void glUniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix2x4dv(location, count, transpose, value);}
inline void glUniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix2x4fv(location, count, transpose, value);}
inline void glUniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix3dv(location, count, transpose, value);}
inline void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix3fv(location, count, transpose, value);}
inline void glUniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix3x2dv(location, count, transpose, value);}
inline void glUniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix3x2fv(location, count, transpose, value);}
inline void glUniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix3x4dv(location, count, transpose, value);}
inline void glUniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix3x4fv(location, count, transpose, value);}
inline void glUniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix4dv(location, count, transpose, value);}
inline void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix4fv(location, count, transpose, value);}
inline void glUniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix4x2dv(location, count, transpose, value);}
inline void glUniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix4x2fv(location, count, transpose, value);}
inline void glUniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value){return _gl_loader_gluniformmatrix4x3dv(location, count, transpose, value);}
inline void glUniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value){return _gl_loader_gluniformmatrix4x3fv(location, count, transpose, value);}
inline void glUniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices){return _gl_loader_gluniformsubroutinesuiv(shadertype, count, indices);}
inline GLboolean glUnmapBuffer(GLenum target){return _gl_loader_glunmapbuffer(target);}
inline GLboolean glUnmapNamedBuffer(GLuint buffer){return _gl_loader_glunmapnamedbuffer(buffer);}
inline void glUseProgram(GLuint program){return _gl_loader_gluseprogram(program);}
inline void glUseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program){return _gl_loader_gluseprogramstages(pipeline, stages, program);}
inline void glValidateProgram(GLuint program){return _gl_loader_glvalidateprogram(program);}
inline void glValidateProgramPipeline(GLuint pipeline){return _gl_loader_glvalidateprogrampipeline(pipeline);}
inline void glVertex2d(GLdouble x, GLdouble y){return _gl_loader_glvertex2d(x, y);}
inline void glVertex2dv(const GLdouble * v){return _gl_loader_glvertex2dv(v);}
inline void glVertex2f(GLfloat x, GLfloat y){return _gl_loader_glvertex2f(x, y);}
inline void glVertex2fv(const GLfloat * v){return _gl_loader_glvertex2fv(v);}
inline void glVertex2i(GLint x, GLint y){return _gl_loader_glvertex2i(x, y);}
inline void glVertex2iv(const GLint * v){return _gl_loader_glvertex2iv(v);}
inline void glVertex2s(GLshort x, GLshort y){return _gl_loader_glvertex2s(x, y);}
inline void glVertex2sv(const GLshort * v){return _gl_loader_glvertex2sv(v);}
inline void glVertex3d(GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glvertex3d(x, y, z);}
inline void glVertex3dv(const GLdouble * v){return _gl_loader_glvertex3dv(v);}
inline void glVertex3f(GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glvertex3f(x, y, z);}
inline void glVertex3fv(const GLfloat * v){return _gl_loader_glvertex3fv(v);}
inline void glVertex3i(GLint x, GLint y, GLint z){return _gl_loader_glvertex3i(x, y, z);}
inline void glVertex3iv(const GLint * v){return _gl_loader_glvertex3iv(v);}
inline void glVertex3s(GLshort x, GLshort y, GLshort z){return _gl_loader_glvertex3s(x, y, z);}
inline void glVertex3sv(const GLshort * v){return _gl_loader_glvertex3sv(v);}
inline void glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w){return _gl_loader_glvertex4d(x, y, z, w);}
inline void glVertex4dv(const GLdouble * v){return _gl_loader_glvertex4dv(v);}
inline void glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w){return _gl_loader_glvertex4f(x, y, z, w);}
inline void glVertex4fv(const GLfloat * v){return _gl_loader_glvertex4fv(v);}
inline void glVertex4i(GLint x, GLint y, GLint z, GLint w){return _gl_loader_glvertex4i(x, y, z, w);}
inline void glVertex4iv(const GLint * v){return _gl_loader_glvertex4iv(v);}
inline void glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w){return _gl_loader_glvertex4s(x, y, z, w);}
inline void glVertex4sv(const GLshort * v){return _gl_loader_glvertex4sv(v);}
inline void glVertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex){return _gl_loader_glvertexarrayattribbinding(vaobj, attribindex, bindingindex);}
inline void glVertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){return _gl_loader_glvertexarrayattribformat(vaobj, attribindex, size, type, normalized, relativeoffset);}
inline void glVertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){return _gl_loader_glvertexarrayattribiformat(vaobj, attribindex, size, type, relativeoffset);}
inline void glVertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){return _gl_loader_glvertexarrayattriblformat(vaobj, attribindex, size, type, relativeoffset);}
inline void glVertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor){return _gl_loader_glvertexarraybindingdivisor(vaobj, bindingindex, divisor);}
inline void glVertexArrayElementBuffer(GLuint vaobj, GLuint buffer){return _gl_loader_glvertexarrayelementbuffer(vaobj, buffer);}
inline void glVertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride){return _gl_loader_glvertexarrayvertexbuffer(vaobj, bindingindex, buffer, offset, stride);}
inline void glVertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides){return _gl_loader_glvertexarrayvertexbuffers(vaobj, first, count, buffers, offsets, strides);}
inline void glVertexAttrib1d(GLuint index, GLdouble x){return _gl_loader_glvertexattrib1d(index, x);}
inline void glVertexAttrib1dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattrib1dv(index, v);}
inline void glVertexAttrib1f(GLuint index, GLfloat x){return _gl_loader_glvertexattrib1f(index, x);}
inline void glVertexAttrib1fv(GLuint index, const GLfloat * v){return _gl_loader_glvertexattrib1fv(index, v);}
inline void glVertexAttrib1s(GLuint index, GLshort x){return _gl_loader_glvertexattrib1s(index, x);}
inline void glVertexAttrib1sv(GLuint index, const GLshort * v){return _gl_loader_glvertexattrib1sv(index, v);}
inline void glVertexAttrib2d(GLuint index, GLdouble x, GLdouble y){return _gl_loader_glvertexattrib2d(index, x, y);}
inline void glVertexAttrib2dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattrib2dv(index, v);}
inline void glVertexAttrib2f(GLuint index, GLfloat x, GLfloat y){return _gl_loader_glvertexattrib2f(index, x, y);}
inline void glVertexAttrib2fv(GLuint index, const GLfloat * v){return _gl_loader_glvertexattrib2fv(index, v);}
inline void glVertexAttrib2s(GLuint index, GLshort x, GLshort y){return _gl_loader_glvertexattrib2s(index, x, y);}
inline void glVertexAttrib2sv(GLuint index, const GLshort * v){return _gl_loader_glvertexattrib2sv(index, v);}
inline void glVertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glvertexattrib3d(index, x, y, z);}
inline void glVertexAttrib3dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattrib3dv(index, v);}
inline void glVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glvertexattrib3f(index, x, y, z);}
inline void glVertexAttrib3fv(GLuint index, const GLfloat * v){return _gl_loader_glvertexattrib3fv(index, v);}
inline void glVertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z){return _gl_loader_glvertexattrib3s(index, x, y, z);}
inline void glVertexAttrib3sv(GLuint index, const GLshort * v){return _gl_loader_glvertexattrib3sv(index, v);}
inline void glVertexAttrib4Nbv(GLuint index, const GLbyte * v){return _gl_loader_glvertexattrib4nbv(index, v);}
inline void glVertexAttrib4Niv(GLuint index, const GLint * v){return _gl_loader_glvertexattrib4niv(index, v);}
inline void glVertexAttrib4Nsv(GLuint index, const GLshort * v){return _gl_loader_glvertexattrib4nsv(index, v);}
inline void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w){return _gl_loader_glvertexattrib4nub(index, x, y, z, w);}
inline void glVertexAttrib4Nubv(GLuint index, const GLubyte * v){return _gl_loader_glvertexattrib4nubv(index, v);}
inline void glVertexAttrib4Nuiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattrib4nuiv(index, v);}
inline void glVertexAttrib4Nusv(GLuint index, const GLushort * v){return _gl_loader_glvertexattrib4nusv(index, v);}
inline void glVertexAttrib4bv(GLuint index, const GLbyte * v){return _gl_loader_glvertexattrib4bv(index, v);}
inline void glVertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){return _gl_loader_glvertexattrib4d(index, x, y, z, w);}
inline void glVertexAttrib4dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattrib4dv(index, v);}
inline void glVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w){return _gl_loader_glvertexattrib4f(index, x, y, z, w);}
inline void glVertexAttrib4fv(GLuint index, const GLfloat * v){return _gl_loader_glvertexattrib4fv(index, v);}
inline void glVertexAttrib4iv(GLuint index, const GLint * v){return _gl_loader_glvertexattrib4iv(index, v);}
inline void glVertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w){return _gl_loader_glvertexattrib4s(index, x, y, z, w);}
inline void glVertexAttrib4sv(GLuint index, const GLshort * v){return _gl_loader_glvertexattrib4sv(index, v);}
inline void glVertexAttrib4ubv(GLuint index, const GLubyte * v){return _gl_loader_glvertexattrib4ubv(index, v);}
inline void glVertexAttrib4uiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattrib4uiv(index, v);}
inline void glVertexAttrib4usv(GLuint index, const GLushort * v){return _gl_loader_glvertexattrib4usv(index, v);}
inline void glVertexAttribBinding(GLuint attribindex, GLuint bindingindex){return _gl_loader_glvertexattribbinding(attribindex, bindingindex);}
inline void glVertexAttribDivisor(GLuint index, GLuint divisor){return _gl_loader_glvertexattribdivisor(index, divisor);}
inline void glVertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset){return _gl_loader_glvertexattribformat(attribindex, size, type, normalized, relativeoffset);}
inline void glVertexAttribI1i(GLuint index, GLint x){return _gl_loader_glvertexattribi1i(index, x);}
inline void glVertexAttribI1iv(GLuint index, const GLint * v){return _gl_loader_glvertexattribi1iv(index, v);}
inline void glVertexAttribI1ui(GLuint index, GLuint x){return _gl_loader_glvertexattribi1ui(index, x);}
inline void glVertexAttribI1uiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattribi1uiv(index, v);}
inline void glVertexAttribI2i(GLuint index, GLint x, GLint y){return _gl_loader_glvertexattribi2i(index, x, y);}
inline void glVertexAttribI2iv(GLuint index, const GLint * v){return _gl_loader_glvertexattribi2iv(index, v);}
inline void glVertexAttribI2ui(GLuint index, GLuint x, GLuint y){return _gl_loader_glvertexattribi2ui(index, x, y);}
inline void glVertexAttribI2uiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattribi2uiv(index, v);}
inline void glVertexAttribI3i(GLuint index, GLint x, GLint y, GLint z){return _gl_loader_glvertexattribi3i(index, x, y, z);}
inline void glVertexAttribI3iv(GLuint index, const GLint * v){return _gl_loader_glvertexattribi3iv(index, v);}
inline void glVertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z){return _gl_loader_glvertexattribi3ui(index, x, y, z);}
inline void glVertexAttribI3uiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattribi3uiv(index, v);}
inline void glVertexAttribI4bv(GLuint index, const GLbyte * v){return _gl_loader_glvertexattribi4bv(index, v);}
inline void glVertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w){return _gl_loader_glvertexattribi4i(index, x, y, z, w);}
inline void glVertexAttribI4iv(GLuint index, const GLint * v){return _gl_loader_glvertexattribi4iv(index, v);}
inline void glVertexAttribI4sv(GLuint index, const GLshort * v){return _gl_loader_glvertexattribi4sv(index, v);}
inline void glVertexAttribI4ubv(GLuint index, const GLubyte * v){return _gl_loader_glvertexattribi4ubv(index, v);}
inline void glVertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w){return _gl_loader_glvertexattribi4ui(index, x, y, z, w);}
inline void glVertexAttribI4uiv(GLuint index, const GLuint * v){return _gl_loader_glvertexattribi4uiv(index, v);}
inline void glVertexAttribI4usv(GLuint index, const GLushort * v){return _gl_loader_glvertexattribi4usv(index, v);}
inline void glVertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){return _gl_loader_glvertexattribiformat(attribindex, size, type, relativeoffset);}
inline void glVertexAttribIPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glvertexattribipointer(index, size, type, stride, pointer);}
inline void glVertexAttribL1d(GLuint index, GLdouble x){return _gl_loader_glvertexattribl1d(index, x);}
inline void glVertexAttribL1dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattribl1dv(index, v);}
inline void glVertexAttribL2d(GLuint index, GLdouble x, GLdouble y){return _gl_loader_glvertexattribl2d(index, x, y);}
inline void glVertexAttribL2dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattribl2dv(index, v);}
inline void glVertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glvertexattribl3d(index, x, y, z);}
inline void glVertexAttribL3dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattribl3dv(index, v);}
inline void glVertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w){return _gl_loader_glvertexattribl4d(index, x, y, z, w);}
inline void glVertexAttribL4dv(GLuint index, const GLdouble * v){return _gl_loader_glvertexattribl4dv(index, v);}
inline void glVertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset){return _gl_loader_glvertexattriblformat(attribindex, size, type, relativeoffset);}
inline void glVertexAttribLPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glvertexattriblpointer(index, size, type, stride, pointer);}
inline void glVertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){return _gl_loader_glvertexattribp1ui(index, type, normalized, value);}
inline void glVertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){return _gl_loader_glvertexattribp1uiv(index, type, normalized, value);}
inline void glVertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){return _gl_loader_glvertexattribp2ui(index, type, normalized, value);}
inline void glVertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){return _gl_loader_glvertexattribp2uiv(index, type, normalized, value);}
inline void glVertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){return _gl_loader_glvertexattribp3ui(index, type, normalized, value);}
inline void glVertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){return _gl_loader_glvertexattribp3uiv(index, type, normalized, value);}
inline void glVertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value){return _gl_loader_glvertexattribp4ui(index, type, normalized, value);}
inline void glVertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value){return _gl_loader_glvertexattribp4uiv(index, type, normalized, value);}
inline void glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer){return _gl_loader_glvertexattribpointer(index, size, type, normalized, stride, pointer);}
inline void glVertexBindingDivisor(GLuint bindingindex, GLuint divisor){return _gl_loader_glvertexbindingdivisor(bindingindex, divisor);}
inline void glVertexP2ui(GLenum type, GLuint value){return _gl_loader_glvertexp2ui(type, value);}
inline void glVertexP2uiv(GLenum type, const GLuint * value){return _gl_loader_glvertexp2uiv(type, value);}
inline void glVertexP3ui(GLenum type, GLuint value){return _gl_loader_glvertexp3ui(type, value);}
inline void glVertexP3uiv(GLenum type, const GLuint * value){return _gl_loader_glvertexp3uiv(type, value);}
inline void glVertexP4ui(GLenum type, GLuint value){return _gl_loader_glvertexp4ui(type, value);}
inline void glVertexP4uiv(GLenum type, const GLuint * value){return _gl_loader_glvertexp4uiv(type, value);}
inline void glVertexPointer(GLint size, GLenum type, GLsizei stride, const void * pointer){return _gl_loader_glvertexpointer(size, type, stride, pointer);}
inline void glViewport(GLint x, GLint y, GLsizei width, GLsizei height){return _gl_loader_glviewport(x, y, width, height);}
inline void glViewportArrayv(GLuint first, GLsizei count, const GLfloat * v){return _gl_loader_glviewportarrayv(first, count, v);}
inline void glViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h){return _gl_loader_glviewportindexedf(index, x, y, w, h);}
inline void glViewportIndexedfv(GLuint index, const GLfloat * v){return _gl_loader_glviewportindexedfv(index, v);}
inline void glWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout){return _gl_loader_glwaitsync(sync, flags, timeout);}
inline void glWindowPos2d(GLdouble x, GLdouble y){return _gl_loader_glwindowpos2d(x, y);}
inline void glWindowPos2dv(const GLdouble * v){return _gl_loader_glwindowpos2dv(v);}
inline void glWindowPos2f(GLfloat x, GLfloat y){return _gl_loader_glwindowpos2f(x, y);}
inline void glWindowPos2fv(const GLfloat * v){return _gl_loader_glwindowpos2fv(v);}
inline void glWindowPos2i(GLint x, GLint y){return _gl_loader_glwindowpos2i(x, y);}
inline void glWindowPos2iv(const GLint * v){return _gl_loader_glwindowpos2iv(v);}
inline void glWindowPos2s(GLshort x, GLshort y){return _gl_loader_glwindowpos2s(x, y);}
inline void glWindowPos2sv(const GLshort * v){return _gl_loader_glwindowpos2sv(v);}
inline void glWindowPos3d(GLdouble x, GLdouble y, GLdouble z){return _gl_loader_glwindowpos3d(x, y, z);}
inline void glWindowPos3dv(const GLdouble * v){return _gl_loader_glwindowpos3dv(v);}
inline void glWindowPos3f(GLfloat x, GLfloat y, GLfloat z){return _gl_loader_glwindowpos3f(x, y, z);}
inline void glWindowPos3fv(const GLfloat * v){return _gl_loader_glwindowpos3fv(v);}
inline void glWindowPos3i(GLint x, GLint y, GLint z){return _gl_loader_glwindowpos3i(x, y, z);}
inline void glWindowPos3iv(const GLint * v){return _gl_loader_glwindowpos3iv(v);}
inline void glWindowPos3s(GLshort x, GLshort y, GLshort z){return _gl_loader_glwindowpos3s(x, y, z);}
inline void glWindowPos3sv(const GLshort * v){return _gl_loader_glwindowpos3sv(v);}


void loadGL(){
	open_gl();
	_gl_loader_glaccum = (PFNGLACCUMPROC)get_proc("glAccum");
	_gl_loader_glactiveshaderprogram = (PFNGLACTIVESHADERPROGRAMPROC)get_proc("glActiveShaderProgram");
	_gl_loader_glactivetexture = (PFNGLACTIVETEXTUREPROC)get_proc("glActiveTexture");
	_gl_loader_glalphafunc = (PFNGLALPHAFUNCPROC)get_proc("glAlphaFunc");
	_gl_loader_glaretexturesresident = (PFNGLARETEXTURESRESIDENTPROC)get_proc("glAreTexturesResident");
	_gl_loader_glarrayelement = (PFNGLARRAYELEMENTPROC)get_proc("glArrayElement");
	_gl_loader_glattachshader = (PFNGLATTACHSHADERPROC)get_proc("glAttachShader");
	_gl_loader_glbegin = (PFNGLBEGINPROC)get_proc("glBegin");
	_gl_loader_glbeginconditionalrender = (PFNGLBEGINCONDITIONALRENDERPROC)get_proc("glBeginConditionalRender");
	_gl_loader_glbeginquery = (PFNGLBEGINQUERYPROC)get_proc("glBeginQuery");
	_gl_loader_glbeginqueryindexed = (PFNGLBEGINQUERYINDEXEDPROC)get_proc("glBeginQueryIndexed");
	_gl_loader_glbegintransformfeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)get_proc("glBeginTransformFeedback");
	_gl_loader_glbindattriblocation = (PFNGLBINDATTRIBLOCATIONPROC)get_proc("glBindAttribLocation");
	_gl_loader_glbindbuffer = (PFNGLBINDBUFFERPROC)get_proc("glBindBuffer");
	_gl_loader_glbindbufferbase = (PFNGLBINDBUFFERBASEPROC)get_proc("glBindBufferBase");
	_gl_loader_glbindbufferrange = (PFNGLBINDBUFFERRANGEPROC)get_proc("glBindBufferRange");
	_gl_loader_glbindbuffersbase = (PFNGLBINDBUFFERSBASEPROC)get_proc("glBindBuffersBase");
	_gl_loader_glbindbuffersrange = (PFNGLBINDBUFFERSRANGEPROC)get_proc("glBindBuffersRange");
	_gl_loader_glbindfragdatalocation = (PFNGLBINDFRAGDATALOCATIONPROC)get_proc("glBindFragDataLocation");
	_gl_loader_glbindfragdatalocationindexed = (PFNGLBINDFRAGDATALOCATIONINDEXEDPROC)get_proc("glBindFragDataLocationIndexed");
	_gl_loader_glbindframebuffer = (PFNGLBINDFRAMEBUFFERPROC)get_proc("glBindFramebuffer");
	_gl_loader_glbindimagetexture = (PFNGLBINDIMAGETEXTUREPROC)get_proc("glBindImageTexture");
	_gl_loader_glbindimagetextures = (PFNGLBINDIMAGETEXTURESPROC)get_proc("glBindImageTextures");
	_gl_loader_glbindprogrampipeline = (PFNGLBINDPROGRAMPIPELINEPROC)get_proc("glBindProgramPipeline");
	_gl_loader_glbindrenderbuffer = (PFNGLBINDRENDERBUFFERPROC)get_proc("glBindRenderbuffer");
	_gl_loader_glbindsampler = (PFNGLBINDSAMPLERPROC)get_proc("glBindSampler");
	_gl_loader_glbindsamplers = (PFNGLBINDSAMPLERSPROC)get_proc("glBindSamplers");
	_gl_loader_glbindtexture = (PFNGLBINDTEXTUREPROC)get_proc("glBindTexture");
	_gl_loader_glbindtextureunit = (PFNGLBINDTEXTUREUNITPROC)get_proc("glBindTextureUnit");
	_gl_loader_glbindtextures = (PFNGLBINDTEXTURESPROC)get_proc("glBindTextures");
	_gl_loader_glbindtransformfeedback = (PFNGLBINDTRANSFORMFEEDBACKPROC)get_proc("glBindTransformFeedback");
	_gl_loader_glbindvertexarray = (PFNGLBINDVERTEXARRAYPROC)get_proc("glBindVertexArray");
	_gl_loader_glbindvertexbuffer = (PFNGLBINDVERTEXBUFFERPROC)get_proc("glBindVertexBuffer");
	_gl_loader_glbindvertexbuffers = (PFNGLBINDVERTEXBUFFERSPROC)get_proc("glBindVertexBuffers");
	_gl_loader_glbitmap = (PFNGLBITMAPPROC)get_proc("glBitmap");
	_gl_loader_glblendcolor = (PFNGLBLENDCOLORPROC)get_proc("glBlendColor");
	_gl_loader_glblendequation = (PFNGLBLENDEQUATIONPROC)get_proc("glBlendEquation");
	_gl_loader_glblendequationseparate = (PFNGLBLENDEQUATIONSEPARATEPROC)get_proc("glBlendEquationSeparate");
	_gl_loader_glblendequationseparatei = (PFNGLBLENDEQUATIONSEPARATEIPROC)get_proc("glBlendEquationSeparatei");
	_gl_loader_glblendequationi = (PFNGLBLENDEQUATIONIPROC)get_proc("glBlendEquationi");
	_gl_loader_glblendfunc = (PFNGLBLENDFUNCPROC)get_proc("glBlendFunc");
	_gl_loader_glblendfuncseparate = (PFNGLBLENDFUNCSEPARATEPROC)get_proc("glBlendFuncSeparate");
	_gl_loader_glblendfuncseparatei = (PFNGLBLENDFUNCSEPARATEIPROC)get_proc("glBlendFuncSeparatei");
	_gl_loader_glblendfunci = (PFNGLBLENDFUNCIPROC)get_proc("glBlendFunci");
	_gl_loader_glblitframebuffer = (PFNGLBLITFRAMEBUFFERPROC)get_proc("glBlitFramebuffer");
	_gl_loader_glblitnamedframebuffer = (PFNGLBLITNAMEDFRAMEBUFFERPROC)get_proc("glBlitNamedFramebuffer");
	_gl_loader_glbufferdata = (PFNGLBUFFERDATAPROC)get_proc("glBufferData");
	_gl_loader_glbufferstorage = (PFNGLBUFFERSTORAGEPROC)get_proc("glBufferStorage");
	_gl_loader_glbuffersubdata = (PFNGLBUFFERSUBDATAPROC)get_proc("glBufferSubData");
	_gl_loader_glcalllist = (PFNGLCALLLISTPROC)get_proc("glCallList");
	_gl_loader_glcalllists = (PFNGLCALLLISTSPROC)get_proc("glCallLists");
	_gl_loader_glcheckframebufferstatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)get_proc("glCheckFramebufferStatus");
	_gl_loader_glchecknamedframebufferstatus = (PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC)get_proc("glCheckNamedFramebufferStatus");
	_gl_loader_glclampcolor = (PFNGLCLAMPCOLORPROC)get_proc("glClampColor");
	_gl_loader_glclear = (PFNGLCLEARPROC)get_proc("glClear");
	_gl_loader_glclearaccum = (PFNGLCLEARACCUMPROC)get_proc("glClearAccum");
	_gl_loader_glclearbufferdata = (PFNGLCLEARBUFFERDATAPROC)get_proc("glClearBufferData");
	_gl_loader_glclearbuffersubdata = (PFNGLCLEARBUFFERSUBDATAPROC)get_proc("glClearBufferSubData");
	_gl_loader_glclearbufferfi = (PFNGLCLEARBUFFERFIPROC)get_proc("glClearBufferfi");
	_gl_loader_glclearbufferfv = (PFNGLCLEARBUFFERFVPROC)get_proc("glClearBufferfv");
	_gl_loader_glclearbufferiv = (PFNGLCLEARBUFFERIVPROC)get_proc("glClearBufferiv");
	_gl_loader_glclearbufferuiv = (PFNGLCLEARBUFFERUIVPROC)get_proc("glClearBufferuiv");
	_gl_loader_glclearcolor = (PFNGLCLEARCOLORPROC)get_proc("glClearColor");
	_gl_loader_glcleardepth = (PFNGLCLEARDEPTHPROC)get_proc("glClearDepth");
	_gl_loader_glcleardepthf = (PFNGLCLEARDEPTHFPROC)get_proc("glClearDepthf");
	_gl_loader_glclearindex = (PFNGLCLEARINDEXPROC)get_proc("glClearIndex");
	_gl_loader_glclearnamedbufferdata = (PFNGLCLEARNAMEDBUFFERDATAPROC)get_proc("glClearNamedBufferData");
	_gl_loader_glclearnamedbuffersubdata = (PFNGLCLEARNAMEDBUFFERSUBDATAPROC)get_proc("glClearNamedBufferSubData");
	_gl_loader_glclearnamedframebufferfi = (PFNGLCLEARNAMEDFRAMEBUFFERFIPROC)get_proc("glClearNamedFramebufferfi");
	_gl_loader_glclearnamedframebufferfv = (PFNGLCLEARNAMEDFRAMEBUFFERFVPROC)get_proc("glClearNamedFramebufferfv");
	_gl_loader_glclearnamedframebufferiv = (PFNGLCLEARNAMEDFRAMEBUFFERIVPROC)get_proc("glClearNamedFramebufferiv");
	_gl_loader_glclearnamedframebufferuiv = (PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC)get_proc("glClearNamedFramebufferuiv");
	_gl_loader_glclearstencil = (PFNGLCLEARSTENCILPROC)get_proc("glClearStencil");
	_gl_loader_glclearteximage = (PFNGLCLEARTEXIMAGEPROC)get_proc("glClearTexImage");
	_gl_loader_glcleartexsubimage = (PFNGLCLEARTEXSUBIMAGEPROC)get_proc("glClearTexSubImage");
	_gl_loader_glclientactivetexture = (PFNGLCLIENTACTIVETEXTUREPROC)get_proc("glClientActiveTexture");
	_gl_loader_glclientwaitsync = (PFNGLCLIENTWAITSYNCPROC)get_proc("glClientWaitSync");
	_gl_loader_glclipcontrol = (PFNGLCLIPCONTROLPROC)get_proc("glClipControl");
	_gl_loader_glclipplane = (PFNGLCLIPPLANEPROC)get_proc("glClipPlane");
	_gl_loader_glcolor3b = (PFNGLCOLOR3BPROC)get_proc("glColor3b");
	_gl_loader_glcolor3bv = (PFNGLCOLOR3BVPROC)get_proc("glColor3bv");
	_gl_loader_glcolor3d = (PFNGLCOLOR3DPROC)get_proc("glColor3d");
	_gl_loader_glcolor3dv = (PFNGLCOLOR3DVPROC)get_proc("glColor3dv");
	_gl_loader_glcolor3f = (PFNGLCOLOR3FPROC)get_proc("glColor3f");
	_gl_loader_glcolor3fv = (PFNGLCOLOR3FVPROC)get_proc("glColor3fv");
	_gl_loader_glcolor3i = (PFNGLCOLOR3IPROC)get_proc("glColor3i");
	_gl_loader_glcolor3iv = (PFNGLCOLOR3IVPROC)get_proc("glColor3iv");
	_gl_loader_glcolor3s = (PFNGLCOLOR3SPROC)get_proc("glColor3s");
	_gl_loader_glcolor3sv = (PFNGLCOLOR3SVPROC)get_proc("glColor3sv");
	_gl_loader_glcolor3ub = (PFNGLCOLOR3UBPROC)get_proc("glColor3ub");
	_gl_loader_glcolor3ubv = (PFNGLCOLOR3UBVPROC)get_proc("glColor3ubv");
	_gl_loader_glcolor3ui = (PFNGLCOLOR3UIPROC)get_proc("glColor3ui");
	_gl_loader_glcolor3uiv = (PFNGLCOLOR3UIVPROC)get_proc("glColor3uiv");
	_gl_loader_glcolor3us = (PFNGLCOLOR3USPROC)get_proc("glColor3us");
	_gl_loader_glcolor3usv = (PFNGLCOLOR3USVPROC)get_proc("glColor3usv");
	_gl_loader_glcolor4b = (PFNGLCOLOR4BPROC)get_proc("glColor4b");
	_gl_loader_glcolor4bv = (PFNGLCOLOR4BVPROC)get_proc("glColor4bv");
	_gl_loader_glcolor4d = (PFNGLCOLOR4DPROC)get_proc("glColor4d");
	_gl_loader_glcolor4dv = (PFNGLCOLOR4DVPROC)get_proc("glColor4dv");
	_gl_loader_glcolor4f = (PFNGLCOLOR4FPROC)get_proc("glColor4f");
	_gl_loader_glcolor4fv = (PFNGLCOLOR4FVPROC)get_proc("glColor4fv");
	_gl_loader_glcolor4i = (PFNGLCOLOR4IPROC)get_proc("glColor4i");
	_gl_loader_glcolor4iv = (PFNGLCOLOR4IVPROC)get_proc("glColor4iv");
	_gl_loader_glcolor4s = (PFNGLCOLOR4SPROC)get_proc("glColor4s");
	_gl_loader_glcolor4sv = (PFNGLCOLOR4SVPROC)get_proc("glColor4sv");
	_gl_loader_glcolor4ub = (PFNGLCOLOR4UBPROC)get_proc("glColor4ub");
	_gl_loader_glcolor4ubv = (PFNGLCOLOR4UBVPROC)get_proc("glColor4ubv");
	_gl_loader_glcolor4ui = (PFNGLCOLOR4UIPROC)get_proc("glColor4ui");
	_gl_loader_glcolor4uiv = (PFNGLCOLOR4UIVPROC)get_proc("glColor4uiv");
	_gl_loader_glcolor4us = (PFNGLCOLOR4USPROC)get_proc("glColor4us");
	_gl_loader_glcolor4usv = (PFNGLCOLOR4USVPROC)get_proc("glColor4usv");
	_gl_loader_glcolormask = (PFNGLCOLORMASKPROC)get_proc("glColorMask");
	_gl_loader_glcolormaski = (PFNGLCOLORMASKIPROC)get_proc("glColorMaski");
	_gl_loader_glcolormaterial = (PFNGLCOLORMATERIALPROC)get_proc("glColorMaterial");
	_gl_loader_glcolorp3ui = (PFNGLCOLORP3UIPROC)get_proc("glColorP3ui");
	_gl_loader_glcolorp3uiv = (PFNGLCOLORP3UIVPROC)get_proc("glColorP3uiv");
	_gl_loader_glcolorp4ui = (PFNGLCOLORP4UIPROC)get_proc("glColorP4ui");
	_gl_loader_glcolorp4uiv = (PFNGLCOLORP4UIVPROC)get_proc("glColorP4uiv");
	_gl_loader_glcolorpointer = (PFNGLCOLORPOINTERPROC)get_proc("glColorPointer");
	_gl_loader_glcompileshader = (PFNGLCOMPILESHADERPROC)get_proc("glCompileShader");
	_gl_loader_glcompressedteximage1d = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)get_proc("glCompressedTexImage1D");
	_gl_loader_glcompressedteximage2d = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)get_proc("glCompressedTexImage2D");
	_gl_loader_glcompressedteximage3d = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)get_proc("glCompressedTexImage3D");
	_gl_loader_glcompressedtexsubimage1d = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)get_proc("glCompressedTexSubImage1D");
	_gl_loader_glcompressedtexsubimage2d = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)get_proc("glCompressedTexSubImage2D");
	_gl_loader_glcompressedtexsubimage3d = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)get_proc("glCompressedTexSubImage3D");
	_gl_loader_glcompressedtexturesubimage1d = (PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC)get_proc("glCompressedTextureSubImage1D");
	_gl_loader_glcompressedtexturesubimage2d = (PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC)get_proc("glCompressedTextureSubImage2D");
	_gl_loader_glcompressedtexturesubimage3d = (PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC)get_proc("glCompressedTextureSubImage3D");
	_gl_loader_glcopybuffersubdata = (PFNGLCOPYBUFFERSUBDATAPROC)get_proc("glCopyBufferSubData");
	_gl_loader_glcopyimagesubdata = (PFNGLCOPYIMAGESUBDATAPROC)get_proc("glCopyImageSubData");
	_gl_loader_glcopynamedbuffersubdata = (PFNGLCOPYNAMEDBUFFERSUBDATAPROC)get_proc("glCopyNamedBufferSubData");
	_gl_loader_glcopypixels = (PFNGLCOPYPIXELSPROC)get_proc("glCopyPixels");
	_gl_loader_glcopyteximage1d = (PFNGLCOPYTEXIMAGE1DPROC)get_proc("glCopyTexImage1D");
	_gl_loader_glcopyteximage2d = (PFNGLCOPYTEXIMAGE2DPROC)get_proc("glCopyTexImage2D");
	_gl_loader_glcopytexsubimage1d = (PFNGLCOPYTEXSUBIMAGE1DPROC)get_proc("glCopyTexSubImage1D");
	_gl_loader_glcopytexsubimage2d = (PFNGLCOPYTEXSUBIMAGE2DPROC)get_proc("glCopyTexSubImage2D");
	_gl_loader_glcopytexsubimage3d = (PFNGLCOPYTEXSUBIMAGE3DPROC)get_proc("glCopyTexSubImage3D");
	_gl_loader_glcopytexturesubimage1d = (PFNGLCOPYTEXTURESUBIMAGE1DPROC)get_proc("glCopyTextureSubImage1D");
	_gl_loader_glcopytexturesubimage2d = (PFNGLCOPYTEXTURESUBIMAGE2DPROC)get_proc("glCopyTextureSubImage2D");
	_gl_loader_glcopytexturesubimage3d = (PFNGLCOPYTEXTURESUBIMAGE3DPROC)get_proc("glCopyTextureSubImage3D");
	_gl_loader_glcreatebuffers = (PFNGLCREATEBUFFERSPROC)get_proc("glCreateBuffers");
	_gl_loader_glcreateframebuffers = (PFNGLCREATEFRAMEBUFFERSPROC)get_proc("glCreateFramebuffers");
	_gl_loader_glcreateprogram = (PFNGLCREATEPROGRAMPROC)get_proc("glCreateProgram");
	_gl_loader_glcreateprogrampipelines = (PFNGLCREATEPROGRAMPIPELINESPROC)get_proc("glCreateProgramPipelines");
	_gl_loader_glcreatequeries = (PFNGLCREATEQUERIESPROC)get_proc("glCreateQueries");
	_gl_loader_glcreaterenderbuffers = (PFNGLCREATERENDERBUFFERSPROC)get_proc("glCreateRenderbuffers");
	_gl_loader_glcreatesamplers = (PFNGLCREATESAMPLERSPROC)get_proc("glCreateSamplers");
	_gl_loader_glcreateshader = (PFNGLCREATESHADERPROC)get_proc("glCreateShader");
	_gl_loader_glcreateshaderprogramv = (PFNGLCREATESHADERPROGRAMVPROC)get_proc("glCreateShaderProgramv");
	_gl_loader_glcreatetextures = (PFNGLCREATETEXTURESPROC)get_proc("glCreateTextures");
	_gl_loader_glcreatetransformfeedbacks = (PFNGLCREATETRANSFORMFEEDBACKSPROC)get_proc("glCreateTransformFeedbacks");
	_gl_loader_glcreatevertexarrays = (PFNGLCREATEVERTEXARRAYSPROC)get_proc("glCreateVertexArrays");
	_gl_loader_glcullface = (PFNGLCULLFACEPROC)get_proc("glCullFace");
	_gl_loader_gldebugmessagecallback = (PFNGLDEBUGMESSAGECALLBACKPROC)get_proc("glDebugMessageCallback");
	_gl_loader_gldebugmessagecontrol = (PFNGLDEBUGMESSAGECONTROLPROC)get_proc("glDebugMessageControl");
	_gl_loader_gldebugmessageinsert = (PFNGLDEBUGMESSAGEINSERTPROC)get_proc("glDebugMessageInsert");
	_gl_loader_gldeletebuffers = (PFNGLDELETEBUFFERSPROC)get_proc("glDeleteBuffers");
	_gl_loader_gldeleteframebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)get_proc("glDeleteFramebuffers");
	_gl_loader_gldeletelists = (PFNGLDELETELISTSPROC)get_proc("glDeleteLists");
	_gl_loader_gldeleteprogram = (PFNGLDELETEPROGRAMPROC)get_proc("glDeleteProgram");
	_gl_loader_gldeleteprogrampipelines = (PFNGLDELETEPROGRAMPIPELINESPROC)get_proc("glDeleteProgramPipelines");
	_gl_loader_gldeletequeries = (PFNGLDELETEQUERIESPROC)get_proc("glDeleteQueries");
	_gl_loader_gldeleterenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)get_proc("glDeleteRenderbuffers");
	_gl_loader_gldeletesamplers = (PFNGLDELETESAMPLERSPROC)get_proc("glDeleteSamplers");
	_gl_loader_gldeleteshader = (PFNGLDELETESHADERPROC)get_proc("glDeleteShader");
	_gl_loader_gldeletesync = (PFNGLDELETESYNCPROC)get_proc("glDeleteSync");
	_gl_loader_gldeletetextures = (PFNGLDELETETEXTURESPROC)get_proc("glDeleteTextures");
	_gl_loader_gldeletetransformfeedbacks = (PFNGLDELETETRANSFORMFEEDBACKSPROC)get_proc("glDeleteTransformFeedbacks");
	_gl_loader_gldeletevertexarrays = (PFNGLDELETEVERTEXARRAYSPROC)get_proc("glDeleteVertexArrays");
	_gl_loader_gldepthfunc = (PFNGLDEPTHFUNCPROC)get_proc("glDepthFunc");
	_gl_loader_gldepthmask = (PFNGLDEPTHMASKPROC)get_proc("glDepthMask");
	_gl_loader_gldepthrange = (PFNGLDEPTHRANGEPROC)get_proc("glDepthRange");
	_gl_loader_gldepthrangearrayv = (PFNGLDEPTHRANGEARRAYVPROC)get_proc("glDepthRangeArrayv");
	_gl_loader_gldepthrangeindexed = (PFNGLDEPTHRANGEINDEXEDPROC)get_proc("glDepthRangeIndexed");
	_gl_loader_gldepthrangef = (PFNGLDEPTHRANGEFPROC)get_proc("glDepthRangef");
	_gl_loader_gldetachshader = (PFNGLDETACHSHADERPROC)get_proc("glDetachShader");
	_gl_loader_gldisable = (PFNGLDISABLEPROC)get_proc("glDisable");
	_gl_loader_gldisableclientstate = (PFNGLDISABLECLIENTSTATEPROC)get_proc("glDisableClientState");
	_gl_loader_gldisablevertexarrayattrib = (PFNGLDISABLEVERTEXARRAYATTRIBPROC)get_proc("glDisableVertexArrayAttrib");
	_gl_loader_gldisablevertexattribarray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)get_proc("glDisableVertexAttribArray");
	_gl_loader_gldisablei = (PFNGLDISABLEIPROC)get_proc("glDisablei");
	_gl_loader_gldispatchcompute = (PFNGLDISPATCHCOMPUTEPROC)get_proc("glDispatchCompute");
	_gl_loader_gldispatchcomputeindirect = (PFNGLDISPATCHCOMPUTEINDIRECTPROC)get_proc("glDispatchComputeIndirect");
	_gl_loader_gldrawarrays = (PFNGLDRAWARRAYSPROC)get_proc("glDrawArrays");
	_gl_loader_gldrawarraysindirect = (PFNGLDRAWARRAYSINDIRECTPROC)get_proc("glDrawArraysIndirect");
	_gl_loader_gldrawarraysinstanced = (PFNGLDRAWARRAYSINSTANCEDPROC)get_proc("glDrawArraysInstanced");
	_gl_loader_gldrawarraysinstancedbaseinstance = (PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC)get_proc("glDrawArraysInstancedBaseInstance");
	_gl_loader_gldrawbuffer = (PFNGLDRAWBUFFERPROC)get_proc("glDrawBuffer");
	_gl_loader_gldrawbuffers = (PFNGLDRAWBUFFERSPROC)get_proc("glDrawBuffers");
	_gl_loader_gldrawelements = (PFNGLDRAWELEMENTSPROC)get_proc("glDrawElements");
	_gl_loader_gldrawelementsbasevertex = (PFNGLDRAWELEMENTSBASEVERTEXPROC)get_proc("glDrawElementsBaseVertex");
	_gl_loader_gldrawelementsindirect = (PFNGLDRAWELEMENTSINDIRECTPROC)get_proc("glDrawElementsIndirect");
	_gl_loader_gldrawelementsinstanced = (PFNGLDRAWELEMENTSINSTANCEDPROC)get_proc("glDrawElementsInstanced");
	_gl_loader_gldrawelementsinstancedbaseinstance = (PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC)get_proc("glDrawElementsInstancedBaseInstance");
	_gl_loader_gldrawelementsinstancedbasevertex = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC)get_proc("glDrawElementsInstancedBaseVertex");
	_gl_loader_gldrawelementsinstancedbasevertexbaseinstance = (PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC)get_proc("glDrawElementsInstancedBaseVertexBaseInstance");
	_gl_loader_gldrawpixels = (PFNGLDRAWPIXELSPROC)get_proc("glDrawPixels");
	_gl_loader_gldrawrangeelements = (PFNGLDRAWRANGEELEMENTSPROC)get_proc("glDrawRangeElements");
	_gl_loader_gldrawrangeelementsbasevertex = (PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC)get_proc("glDrawRangeElementsBaseVertex");
	_gl_loader_gldrawtransformfeedback = (PFNGLDRAWTRANSFORMFEEDBACKPROC)get_proc("glDrawTransformFeedback");
	_gl_loader_gldrawtransformfeedbackinstanced = (PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC)get_proc("glDrawTransformFeedbackInstanced");
	_gl_loader_gldrawtransformfeedbackstream = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC)get_proc("glDrawTransformFeedbackStream");
	_gl_loader_gldrawtransformfeedbackstreaminstanced = (PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC)get_proc("glDrawTransformFeedbackStreamInstanced");
	_gl_loader_gledgeflag = (PFNGLEDGEFLAGPROC)get_proc("glEdgeFlag");
	_gl_loader_gledgeflagpointer = (PFNGLEDGEFLAGPOINTERPROC)get_proc("glEdgeFlagPointer");
	_gl_loader_gledgeflagv = (PFNGLEDGEFLAGVPROC)get_proc("glEdgeFlagv");
	_gl_loader_glenable = (PFNGLENABLEPROC)get_proc("glEnable");
	_gl_loader_glenableclientstate = (PFNGLENABLECLIENTSTATEPROC)get_proc("glEnableClientState");
	_gl_loader_glenablevertexarrayattrib = (PFNGLENABLEVERTEXARRAYATTRIBPROC)get_proc("glEnableVertexArrayAttrib");
	_gl_loader_glenablevertexattribarray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)get_proc("glEnableVertexAttribArray");
	_gl_loader_glenablei = (PFNGLENABLEIPROC)get_proc("glEnablei");
	_gl_loader_glend = (PFNGLENDPROC)get_proc("glEnd");
	_gl_loader_glendconditionalrender = (PFNGLENDCONDITIONALRENDERPROC)get_proc("glEndConditionalRender");
	_gl_loader_glendlist = (PFNGLENDLISTPROC)get_proc("glEndList");
	_gl_loader_glendquery = (PFNGLENDQUERYPROC)get_proc("glEndQuery");
	_gl_loader_glendqueryindexed = (PFNGLENDQUERYINDEXEDPROC)get_proc("glEndQueryIndexed");
	_gl_loader_glendtransformfeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)get_proc("glEndTransformFeedback");
	_gl_loader_glevalcoord1d = (PFNGLEVALCOORD1DPROC)get_proc("glEvalCoord1d");
	_gl_loader_glevalcoord1dv = (PFNGLEVALCOORD1DVPROC)get_proc("glEvalCoord1dv");
	_gl_loader_glevalcoord1f = (PFNGLEVALCOORD1FPROC)get_proc("glEvalCoord1f");
	_gl_loader_glevalcoord1fv = (PFNGLEVALCOORD1FVPROC)get_proc("glEvalCoord1fv");
	_gl_loader_glevalcoord2d = (PFNGLEVALCOORD2DPROC)get_proc("glEvalCoord2d");
	_gl_loader_glevalcoord2dv = (PFNGLEVALCOORD2DVPROC)get_proc("glEvalCoord2dv");
	_gl_loader_glevalcoord2f = (PFNGLEVALCOORD2FPROC)get_proc("glEvalCoord2f");
	_gl_loader_glevalcoord2fv = (PFNGLEVALCOORD2FVPROC)get_proc("glEvalCoord2fv");
	_gl_loader_glevalmesh1 = (PFNGLEVALMESH1PROC)get_proc("glEvalMesh1");
	_gl_loader_glevalmesh2 = (PFNGLEVALMESH2PROC)get_proc("glEvalMesh2");
	_gl_loader_glevalpoint1 = (PFNGLEVALPOINT1PROC)get_proc("glEvalPoint1");
	_gl_loader_glevalpoint2 = (PFNGLEVALPOINT2PROC)get_proc("glEvalPoint2");
	_gl_loader_glfeedbackbuffer = (PFNGLFEEDBACKBUFFERPROC)get_proc("glFeedbackBuffer");
	_gl_loader_glfencesync = (PFNGLFENCESYNCPROC)get_proc("glFenceSync");
	_gl_loader_glfinish = (PFNGLFINISHPROC)get_proc("glFinish");
	_gl_loader_glflush = (PFNGLFLUSHPROC)get_proc("glFlush");
	_gl_loader_glflushmappedbufferrange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)get_proc("glFlushMappedBufferRange");
	_gl_loader_glflushmappednamedbufferrange = (PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC)get_proc("glFlushMappedNamedBufferRange");
	_gl_loader_glfogcoordpointer = (PFNGLFOGCOORDPOINTERPROC)get_proc("glFogCoordPointer");
	_gl_loader_glfogcoordd = (PFNGLFOGCOORDDPROC)get_proc("glFogCoordd");
	_gl_loader_glfogcoorddv = (PFNGLFOGCOORDDVPROC)get_proc("glFogCoorddv");
	_gl_loader_glfogcoordf = (PFNGLFOGCOORDFPROC)get_proc("glFogCoordf");
	_gl_loader_glfogcoordfv = (PFNGLFOGCOORDFVPROC)get_proc("glFogCoordfv");
	_gl_loader_glfogf = (PFNGLFOGFPROC)get_proc("glFogf");
	_gl_loader_glfogfv = (PFNGLFOGFVPROC)get_proc("glFogfv");
	_gl_loader_glfogi = (PFNGLFOGIPROC)get_proc("glFogi");
	_gl_loader_glfogiv = (PFNGLFOGIVPROC)get_proc("glFogiv");
	_gl_loader_glframebufferparameteri = (PFNGLFRAMEBUFFERPARAMETERIPROC)get_proc("glFramebufferParameteri");
	_gl_loader_glframebufferrenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)get_proc("glFramebufferRenderbuffer");
	_gl_loader_glframebuffertexture = (PFNGLFRAMEBUFFERTEXTUREPROC)get_proc("glFramebufferTexture");
	_gl_loader_glframebuffertexture1d = (PFNGLFRAMEBUFFERTEXTURE1DPROC)get_proc("glFramebufferTexture1D");
	_gl_loader_glframebuffertexture2d = (PFNGLFRAMEBUFFERTEXTURE2DPROC)get_proc("glFramebufferTexture2D");
	_gl_loader_glframebuffertexture3d = (PFNGLFRAMEBUFFERTEXTURE3DPROC)get_proc("glFramebufferTexture3D");
	_gl_loader_glframebuffertexturelayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)get_proc("glFramebufferTextureLayer");
	_gl_loader_glfrontface = (PFNGLFRONTFACEPROC)get_proc("glFrontFace");
	_gl_loader_glfrustum = (PFNGLFRUSTUMPROC)get_proc("glFrustum");
	_gl_loader_glgenbuffers = (PFNGLGENBUFFERSPROC)get_proc("glGenBuffers");
	_gl_loader_glgenframebuffers = (PFNGLGENFRAMEBUFFERSPROC)get_proc("glGenFramebuffers");
	_gl_loader_glgenlists = (PFNGLGENLISTSPROC)get_proc("glGenLists");
	_gl_loader_glgenprogrampipelines = (PFNGLGENPROGRAMPIPELINESPROC)get_proc("glGenProgramPipelines");
	_gl_loader_glgenqueries = (PFNGLGENQUERIESPROC)get_proc("glGenQueries");
	_gl_loader_glgenrenderbuffers = (PFNGLGENRENDERBUFFERSPROC)get_proc("glGenRenderbuffers");
	_gl_loader_glgensamplers = (PFNGLGENSAMPLERSPROC)get_proc("glGenSamplers");
	_gl_loader_glgentextures = (PFNGLGENTEXTURESPROC)get_proc("glGenTextures");
	_gl_loader_glgentransformfeedbacks = (PFNGLGENTRANSFORMFEEDBACKSPROC)get_proc("glGenTransformFeedbacks");
	_gl_loader_glgenvertexarrays = (PFNGLGENVERTEXARRAYSPROC)get_proc("glGenVertexArrays");
	_gl_loader_glgeneratemipmap = (PFNGLGENERATEMIPMAPPROC)get_proc("glGenerateMipmap");
	_gl_loader_glgeneratetexturemipmap = (PFNGLGENERATETEXTUREMIPMAPPROC)get_proc("glGenerateTextureMipmap");
	_gl_loader_glgetactiveatomiccounterbufferiv = (PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC)get_proc("glGetActiveAtomicCounterBufferiv");
	_gl_loader_glgetactiveattrib = (PFNGLGETACTIVEATTRIBPROC)get_proc("glGetActiveAttrib");
	_gl_loader_glgetactivesubroutinename = (PFNGLGETACTIVESUBROUTINENAMEPROC)get_proc("glGetActiveSubroutineName");
	_gl_loader_glgetactivesubroutineuniformname = (PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC)get_proc("glGetActiveSubroutineUniformName");
	_gl_loader_glgetactivesubroutineuniformiv = (PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC)get_proc("glGetActiveSubroutineUniformiv");
	_gl_loader_glgetactiveuniform = (PFNGLGETACTIVEUNIFORMPROC)get_proc("glGetActiveUniform");
	_gl_loader_glgetactiveuniformblockname = (PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC)get_proc("glGetActiveUniformBlockName");
	_gl_loader_glgetactiveuniformblockiv = (PFNGLGETACTIVEUNIFORMBLOCKIVPROC)get_proc("glGetActiveUniformBlockiv");
	_gl_loader_glgetactiveuniformname = (PFNGLGETACTIVEUNIFORMNAMEPROC)get_proc("glGetActiveUniformName");
	_gl_loader_glgetactiveuniformsiv = (PFNGLGETACTIVEUNIFORMSIVPROC)get_proc("glGetActiveUniformsiv");
	_gl_loader_glgetattachedshaders = (PFNGLGETATTACHEDSHADERSPROC)get_proc("glGetAttachedShaders");
	_gl_loader_glgetattriblocation = (PFNGLGETATTRIBLOCATIONPROC)get_proc("glGetAttribLocation");
	_gl_loader_glgetbooleani_v = (PFNGLGETBOOLEANI_VPROC)get_proc("glGetBooleani_v");
	_gl_loader_glgetbooleanv = (PFNGLGETBOOLEANVPROC)get_proc("glGetBooleanv");
	_gl_loader_glgetbufferparameteri64v = (PFNGLGETBUFFERPARAMETERI64VPROC)get_proc("glGetBufferParameteri64v");
	_gl_loader_glgetbufferparameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)get_proc("glGetBufferParameteriv");
	_gl_loader_glgetbufferpointerv = (PFNGLGETBUFFERPOINTERVPROC)get_proc("glGetBufferPointerv");
	_gl_loader_glgetbuffersubdata = (PFNGLGETBUFFERSUBDATAPROC)get_proc("glGetBufferSubData");
	_gl_loader_glgetclipplane = (PFNGLGETCLIPPLANEPROC)get_proc("glGetClipPlane");
	_gl_loader_glgetcompressedteximage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)get_proc("glGetCompressedTexImage");
	_gl_loader_glgetcompressedtextureimage = (PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC)get_proc("glGetCompressedTextureImage");
	_gl_loader_glgetcompressedtexturesubimage = (PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC)get_proc("glGetCompressedTextureSubImage");
	_gl_loader_glgetdebugmessagelog = (PFNGLGETDEBUGMESSAGELOGPROC)get_proc("glGetDebugMessageLog");
	_gl_loader_glgetdoublei_v = (PFNGLGETDOUBLEI_VPROC)get_proc("glGetDoublei_v");
	_gl_loader_glgetdoublev = (PFNGLGETDOUBLEVPROC)get_proc("glGetDoublev");
	_gl_loader_glgeterror = (PFNGLGETERRORPROC)get_proc("glGetError");
	_gl_loader_glgetfloati_v = (PFNGLGETFLOATI_VPROC)get_proc("glGetFloati_v");
	_gl_loader_glgetfloatv = (PFNGLGETFLOATVPROC)get_proc("glGetFloatv");
	_gl_loader_glgetfragdataindex = (PFNGLGETFRAGDATAINDEXPROC)get_proc("glGetFragDataIndex");
	_gl_loader_glgetfragdatalocation = (PFNGLGETFRAGDATALOCATIONPROC)get_proc("glGetFragDataLocation");
	_gl_loader_glgetframebufferattachmentparameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get_proc("glGetFramebufferAttachmentParameteriv");
	_gl_loader_glgetframebufferparameteriv = (PFNGLGETFRAMEBUFFERPARAMETERIVPROC)get_proc("glGetFramebufferParameteriv");
	_gl_loader_glgetgraphicsresetstatus = (PFNGLGETGRAPHICSRESETSTATUSPROC)get_proc("glGetGraphicsResetStatus");
	_gl_loader_glgetinteger64i_v = (PFNGLGETINTEGER64I_VPROC)get_proc("glGetInteger64i_v");
	_gl_loader_glgetinteger64v = (PFNGLGETINTEGER64VPROC)get_proc("glGetInteger64v");
	_gl_loader_glgetintegeri_v = (PFNGLGETINTEGERI_VPROC)get_proc("glGetIntegeri_v");
	_gl_loader_glgetintegerv = (PFNGLGETINTEGERVPROC)get_proc("glGetIntegerv");
	_gl_loader_glgetinternalformati64v = (PFNGLGETINTERNALFORMATI64VPROC)get_proc("glGetInternalformati64v");
	_gl_loader_glgetinternalformativ = (PFNGLGETINTERNALFORMATIVPROC)get_proc("glGetInternalformativ");
	_gl_loader_glgetlightfv = (PFNGLGETLIGHTFVPROC)get_proc("glGetLightfv");
	_gl_loader_glgetlightiv = (PFNGLGETLIGHTIVPROC)get_proc("glGetLightiv");
	_gl_loader_glgetmapdv = (PFNGLGETMAPDVPROC)get_proc("glGetMapdv");
	_gl_loader_glgetmapfv = (PFNGLGETMAPFVPROC)get_proc("glGetMapfv");
	_gl_loader_glgetmapiv = (PFNGLGETMAPIVPROC)get_proc("glGetMapiv");
	_gl_loader_glgetmaterialfv = (PFNGLGETMATERIALFVPROC)get_proc("glGetMaterialfv");
	_gl_loader_glgetmaterialiv = (PFNGLGETMATERIALIVPROC)get_proc("glGetMaterialiv");
	_gl_loader_glgetmultisamplefv = (PFNGLGETMULTISAMPLEFVPROC)get_proc("glGetMultisamplefv");
	_gl_loader_glgetnamedbufferparameteri64v = (PFNGLGETNAMEDBUFFERPARAMETERI64VPROC)get_proc("glGetNamedBufferParameteri64v");
	_gl_loader_glgetnamedbufferparameteriv = (PFNGLGETNAMEDBUFFERPARAMETERIVPROC)get_proc("glGetNamedBufferParameteriv");
	_gl_loader_glgetnamedbufferpointerv = (PFNGLGETNAMEDBUFFERPOINTERVPROC)get_proc("glGetNamedBufferPointerv");
	_gl_loader_glgetnamedbuffersubdata = (PFNGLGETNAMEDBUFFERSUBDATAPROC)get_proc("glGetNamedBufferSubData");
	_gl_loader_glgetnamedframebufferattachmentparameteriv = (PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC)get_proc("glGetNamedFramebufferAttachmentParameteriv");
	_gl_loader_glgetnamedframebufferparameteriv = (PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC)get_proc("glGetNamedFramebufferParameteriv");
	_gl_loader_glgetnamedrenderbufferparameteriv = (PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC)get_proc("glGetNamedRenderbufferParameteriv");
	_gl_loader_glgetobjectlabel = (PFNGLGETOBJECTLABELPROC)get_proc("glGetObjectLabel");
	_gl_loader_glgetobjectptrlabel = (PFNGLGETOBJECTPTRLABELPROC)get_proc("glGetObjectPtrLabel");
	_gl_loader_glgetpixelmapfv = (PFNGLGETPIXELMAPFVPROC)get_proc("glGetPixelMapfv");
	_gl_loader_glgetpixelmapuiv = (PFNGLGETPIXELMAPUIVPROC)get_proc("glGetPixelMapuiv");
	_gl_loader_glgetpixelmapusv = (PFNGLGETPIXELMAPUSVPROC)get_proc("glGetPixelMapusv");
	_gl_loader_glgetpointerv = (PFNGLGETPOINTERVPROC)get_proc("glGetPointerv");
	_gl_loader_glgetpolygonstipple = (PFNGLGETPOLYGONSTIPPLEPROC)get_proc("glGetPolygonStipple");
	_gl_loader_glgetprogrambinary = (PFNGLGETPROGRAMBINARYPROC)get_proc("glGetProgramBinary");
	_gl_loader_glgetprograminfolog = (PFNGLGETPROGRAMINFOLOGPROC)get_proc("glGetProgramInfoLog");
	_gl_loader_glgetprograminterfaceiv = (PFNGLGETPROGRAMINTERFACEIVPROC)get_proc("glGetProgramInterfaceiv");
	_gl_loader_glgetprogrampipelineinfolog = (PFNGLGETPROGRAMPIPELINEINFOLOGPROC)get_proc("glGetProgramPipelineInfoLog");
	_gl_loader_glgetprogrampipelineiv = (PFNGLGETPROGRAMPIPELINEIVPROC)get_proc("glGetProgramPipelineiv");
	_gl_loader_glgetprogramresourceindex = (PFNGLGETPROGRAMRESOURCEINDEXPROC)get_proc("glGetProgramResourceIndex");
	_gl_loader_glgetprogramresourcelocation = (PFNGLGETPROGRAMRESOURCELOCATIONPROC)get_proc("glGetProgramResourceLocation");
	_gl_loader_glgetprogramresourcelocationindex = (PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC)get_proc("glGetProgramResourceLocationIndex");
	_gl_loader_glgetprogramresourcename = (PFNGLGETPROGRAMRESOURCENAMEPROC)get_proc("glGetProgramResourceName");
	_gl_loader_glgetprogramresourceiv = (PFNGLGETPROGRAMRESOURCEIVPROC)get_proc("glGetProgramResourceiv");
	_gl_loader_glgetprogramstageiv = (PFNGLGETPROGRAMSTAGEIVPROC)get_proc("glGetProgramStageiv");
	_gl_loader_glgetprogramiv = (PFNGLGETPROGRAMIVPROC)get_proc("glGetProgramiv");
	_gl_loader_glgetquerybufferobjecti64v = (PFNGLGETQUERYBUFFEROBJECTI64VPROC)get_proc("glGetQueryBufferObjecti64v");
	_gl_loader_glgetquerybufferobjectiv = (PFNGLGETQUERYBUFFEROBJECTIVPROC)get_proc("glGetQueryBufferObjectiv");
	_gl_loader_glgetquerybufferobjectui64v = (PFNGLGETQUERYBUFFEROBJECTUI64VPROC)get_proc("glGetQueryBufferObjectui64v");
	_gl_loader_glgetquerybufferobjectuiv = (PFNGLGETQUERYBUFFEROBJECTUIVPROC)get_proc("glGetQueryBufferObjectuiv");
	_gl_loader_glgetqueryindexediv = (PFNGLGETQUERYINDEXEDIVPROC)get_proc("glGetQueryIndexediv");
	_gl_loader_glgetqueryobjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)get_proc("glGetQueryObjecti64v");
	_gl_loader_glgetqueryobjectiv = (PFNGLGETQUERYOBJECTIVPROC)get_proc("glGetQueryObjectiv");
	_gl_loader_glgetqueryobjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)get_proc("glGetQueryObjectui64v");
	_gl_loader_glgetqueryobjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)get_proc("glGetQueryObjectuiv");
	_gl_loader_glgetqueryiv = (PFNGLGETQUERYIVPROC)get_proc("glGetQueryiv");
	_gl_loader_glgetrenderbufferparameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)get_proc("glGetRenderbufferParameteriv");
	_gl_loader_glgetsamplerparameteriiv = (PFNGLGETSAMPLERPARAMETERIIVPROC)get_proc("glGetSamplerParameterIiv");
	_gl_loader_glgetsamplerparameteriuiv = (PFNGLGETSAMPLERPARAMETERIUIVPROC)get_proc("glGetSamplerParameterIuiv");
	_gl_loader_glgetsamplerparameterfv = (PFNGLGETSAMPLERPARAMETERFVPROC)get_proc("glGetSamplerParameterfv");
	_gl_loader_glgetsamplerparameteriv = (PFNGLGETSAMPLERPARAMETERIVPROC)get_proc("glGetSamplerParameteriv");
	_gl_loader_glgetshaderinfolog = (PFNGLGETSHADERINFOLOGPROC)get_proc("glGetShaderInfoLog");
	_gl_loader_glgetshaderprecisionformat = (PFNGLGETSHADERPRECISIONFORMATPROC)get_proc("glGetShaderPrecisionFormat");
	_gl_loader_glgetshadersource = (PFNGLGETSHADERSOURCEPROC)get_proc("glGetShaderSource");
	_gl_loader_glgetshaderiv = (PFNGLGETSHADERIVPROC)get_proc("glGetShaderiv");
	_gl_loader_glgetstring = (PFNGLGETSTRINGPROC)get_proc("glGetString");
	_gl_loader_glgetstringi = (PFNGLGETSTRINGIPROC)get_proc("glGetStringi");
	_gl_loader_glgetsubroutineindex = (PFNGLGETSUBROUTINEINDEXPROC)get_proc("glGetSubroutineIndex");
	_gl_loader_glgetsubroutineuniformlocation = (PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC)get_proc("glGetSubroutineUniformLocation");
	_gl_loader_glgetsynciv = (PFNGLGETSYNCIVPROC)get_proc("glGetSynciv");
	_gl_loader_glgettexenvfv = (PFNGLGETTEXENVFVPROC)get_proc("glGetTexEnvfv");
	_gl_loader_glgettexenviv = (PFNGLGETTEXENVIVPROC)get_proc("glGetTexEnviv");
	_gl_loader_glgettexgendv = (PFNGLGETTEXGENDVPROC)get_proc("glGetTexGendv");
	_gl_loader_glgettexgenfv = (PFNGLGETTEXGENFVPROC)get_proc("glGetTexGenfv");
	_gl_loader_glgettexgeniv = (PFNGLGETTEXGENIVPROC)get_proc("glGetTexGeniv");
	_gl_loader_glgetteximage = (PFNGLGETTEXIMAGEPROC)get_proc("glGetTexImage");
	_gl_loader_glgettexlevelparameterfv = (PFNGLGETTEXLEVELPARAMETERFVPROC)get_proc("glGetTexLevelParameterfv");
	_gl_loader_glgettexlevelparameteriv = (PFNGLGETTEXLEVELPARAMETERIVPROC)get_proc("glGetTexLevelParameteriv");
	_gl_loader_glgettexparameteriiv = (PFNGLGETTEXPARAMETERIIVPROC)get_proc("glGetTexParameterIiv");
	_gl_loader_glgettexparameteriuiv = (PFNGLGETTEXPARAMETERIUIVPROC)get_proc("glGetTexParameterIuiv");
	_gl_loader_glgettexparameterfv = (PFNGLGETTEXPARAMETERFVPROC)get_proc("glGetTexParameterfv");
	_gl_loader_glgettexparameteriv = (PFNGLGETTEXPARAMETERIVPROC)get_proc("glGetTexParameteriv");
	_gl_loader_glgettextureimage = (PFNGLGETTEXTUREIMAGEPROC)get_proc("glGetTextureImage");
	_gl_loader_glgettexturelevelparameterfv = (PFNGLGETTEXTURELEVELPARAMETERFVPROC)get_proc("glGetTextureLevelParameterfv");
	_gl_loader_glgettexturelevelparameteriv = (PFNGLGETTEXTURELEVELPARAMETERIVPROC)get_proc("glGetTextureLevelParameteriv");
	_gl_loader_glgettextureparameteriiv = (PFNGLGETTEXTUREPARAMETERIIVPROC)get_proc("glGetTextureParameterIiv");
	_gl_loader_glgettextureparameteriuiv = (PFNGLGETTEXTUREPARAMETERIUIVPROC)get_proc("glGetTextureParameterIuiv");
	_gl_loader_glgettextureparameterfv = (PFNGLGETTEXTUREPARAMETERFVPROC)get_proc("glGetTextureParameterfv");
	_gl_loader_glgettextureparameteriv = (PFNGLGETTEXTUREPARAMETERIVPROC)get_proc("glGetTextureParameteriv");
	_gl_loader_glgettexturesubimage = (PFNGLGETTEXTURESUBIMAGEPROC)get_proc("glGetTextureSubImage");
	_gl_loader_glgettransformfeedbackvarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)get_proc("glGetTransformFeedbackVarying");
	_gl_loader_glgettransformfeedbacki64_v = (PFNGLGETTRANSFORMFEEDBACKI64_VPROC)get_proc("glGetTransformFeedbacki64_v");
	_gl_loader_glgettransformfeedbacki_v = (PFNGLGETTRANSFORMFEEDBACKI_VPROC)get_proc("glGetTransformFeedbacki_v");
	_gl_loader_glgettransformfeedbackiv = (PFNGLGETTRANSFORMFEEDBACKIVPROC)get_proc("glGetTransformFeedbackiv");
	_gl_loader_glgetuniformblockindex = (PFNGLGETUNIFORMBLOCKINDEXPROC)get_proc("glGetUniformBlockIndex");
	_gl_loader_glgetuniformindices = (PFNGLGETUNIFORMINDICESPROC)get_proc("glGetUniformIndices");
	_gl_loader_glgetuniformlocation = (PFNGLGETUNIFORMLOCATIONPROC)get_proc("glGetUniformLocation");
	_gl_loader_glgetuniformsubroutineuiv = (PFNGLGETUNIFORMSUBROUTINEUIVPROC)get_proc("glGetUniformSubroutineuiv");
	_gl_loader_glgetuniformdv = (PFNGLGETUNIFORMDVPROC)get_proc("glGetUniformdv");
	_gl_loader_glgetuniformfv = (PFNGLGETUNIFORMFVPROC)get_proc("glGetUniformfv");
	_gl_loader_glgetuniformiv = (PFNGLGETUNIFORMIVPROC)get_proc("glGetUniformiv");
	_gl_loader_glgetuniformuiv = (PFNGLGETUNIFORMUIVPROC)get_proc("glGetUniformuiv");
	_gl_loader_glgetvertexarrayindexed64iv = (PFNGLGETVERTEXARRAYINDEXED64IVPROC)get_proc("glGetVertexArrayIndexed64iv");
	_gl_loader_glgetvertexarrayindexediv = (PFNGLGETVERTEXARRAYINDEXEDIVPROC)get_proc("glGetVertexArrayIndexediv");
	_gl_loader_glgetvertexarrayiv = (PFNGLGETVERTEXARRAYIVPROC)get_proc("glGetVertexArrayiv");
	_gl_loader_glgetvertexattribiiv = (PFNGLGETVERTEXATTRIBIIVPROC)get_proc("glGetVertexAttribIiv");
	_gl_loader_glgetvertexattribiuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)get_proc("glGetVertexAttribIuiv");
	_gl_loader_glgetvertexattribldv = (PFNGLGETVERTEXATTRIBLDVPROC)get_proc("glGetVertexAttribLdv");
	_gl_loader_glgetvertexattribpointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)get_proc("glGetVertexAttribPointerv");
	_gl_loader_glgetvertexattribdv = (PFNGLGETVERTEXATTRIBDVPROC)get_proc("glGetVertexAttribdv");
	_gl_loader_glgetvertexattribfv = (PFNGLGETVERTEXATTRIBFVPROC)get_proc("glGetVertexAttribfv");
	_gl_loader_glgetvertexattribiv = (PFNGLGETVERTEXATTRIBIVPROC)get_proc("glGetVertexAttribiv");
	_gl_loader_glgetncolortable = (PFNGLGETNCOLORTABLEPROC)get_proc("glGetnColorTable");
	_gl_loader_glgetncompressedteximage = (PFNGLGETNCOMPRESSEDTEXIMAGEPROC)get_proc("glGetnCompressedTexImage");
	_gl_loader_glgetnconvolutionfilter = (PFNGLGETNCONVOLUTIONFILTERPROC)get_proc("glGetnConvolutionFilter");
	_gl_loader_glgetnhistogram = (PFNGLGETNHISTOGRAMPROC)get_proc("glGetnHistogram");
	_gl_loader_glgetnmapdv = (PFNGLGETNMAPDVPROC)get_proc("glGetnMapdv");
	_gl_loader_glgetnmapfv = (PFNGLGETNMAPFVPROC)get_proc("glGetnMapfv");
	_gl_loader_glgetnmapiv = (PFNGLGETNMAPIVPROC)get_proc("glGetnMapiv");
	_gl_loader_glgetnminmax = (PFNGLGETNMINMAXPROC)get_proc("glGetnMinmax");
	_gl_loader_glgetnpixelmapfv = (PFNGLGETNPIXELMAPFVPROC)get_proc("glGetnPixelMapfv");
	_gl_loader_glgetnpixelmapuiv = (PFNGLGETNPIXELMAPUIVPROC)get_proc("glGetnPixelMapuiv");
	_gl_loader_glgetnpixelmapusv = (PFNGLGETNPIXELMAPUSVPROC)get_proc("glGetnPixelMapusv");
	_gl_loader_glgetnpolygonstipple = (PFNGLGETNPOLYGONSTIPPLEPROC)get_proc("glGetnPolygonStipple");
	_gl_loader_glgetnseparablefilter = (PFNGLGETNSEPARABLEFILTERPROC)get_proc("glGetnSeparableFilter");
	_gl_loader_glgetnteximage = (PFNGLGETNTEXIMAGEPROC)get_proc("glGetnTexImage");
	_gl_loader_glgetnuniformdv = (PFNGLGETNUNIFORMDVPROC)get_proc("glGetnUniformdv");
	_gl_loader_glgetnuniformfv = (PFNGLGETNUNIFORMFVPROC)get_proc("glGetnUniformfv");
	_gl_loader_glgetnuniformiv = (PFNGLGETNUNIFORMIVPROC)get_proc("glGetnUniformiv");
	_gl_loader_glgetnuniformuiv = (PFNGLGETNUNIFORMUIVPROC)get_proc("glGetnUniformuiv");
	_gl_loader_glhint = (PFNGLHINTPROC)get_proc("glHint");
	_gl_loader_glindexmask = (PFNGLINDEXMASKPROC)get_proc("glIndexMask");
	_gl_loader_glindexpointer = (PFNGLINDEXPOINTERPROC)get_proc("glIndexPointer");
	_gl_loader_glindexd = (PFNGLINDEXDPROC)get_proc("glIndexd");
	_gl_loader_glindexdv = (PFNGLINDEXDVPROC)get_proc("glIndexdv");
	_gl_loader_glindexf = (PFNGLINDEXFPROC)get_proc("glIndexf");
	_gl_loader_glindexfv = (PFNGLINDEXFVPROC)get_proc("glIndexfv");
	_gl_loader_glindexi = (PFNGLINDEXIPROC)get_proc("glIndexi");
	_gl_loader_glindexiv = (PFNGLINDEXIVPROC)get_proc("glIndexiv");
	_gl_loader_glindexs = (PFNGLINDEXSPROC)get_proc("glIndexs");
	_gl_loader_glindexsv = (PFNGLINDEXSVPROC)get_proc("glIndexsv");
	_gl_loader_glindexub = (PFNGLINDEXUBPROC)get_proc("glIndexub");
	_gl_loader_glindexubv = (PFNGLINDEXUBVPROC)get_proc("glIndexubv");
	_gl_loader_glinitnames = (PFNGLINITNAMESPROC)get_proc("glInitNames");
	_gl_loader_glinterleavedarrays = (PFNGLINTERLEAVEDARRAYSPROC)get_proc("glInterleavedArrays");
	_gl_loader_glinvalidatebufferdata = (PFNGLINVALIDATEBUFFERDATAPROC)get_proc("glInvalidateBufferData");
	_gl_loader_glinvalidatebuffersubdata = (PFNGLINVALIDATEBUFFERSUBDATAPROC)get_proc("glInvalidateBufferSubData");
	_gl_loader_glinvalidateframebuffer = (PFNGLINVALIDATEFRAMEBUFFERPROC)get_proc("glInvalidateFramebuffer");
	_gl_loader_glinvalidatenamedframebufferdata = (PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC)get_proc("glInvalidateNamedFramebufferData");
	_gl_loader_glinvalidatenamedframebuffersubdata = (PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC)get_proc("glInvalidateNamedFramebufferSubData");
	_gl_loader_glinvalidatesubframebuffer = (PFNGLINVALIDATESUBFRAMEBUFFERPROC)get_proc("glInvalidateSubFramebuffer");
	_gl_loader_glinvalidateteximage = (PFNGLINVALIDATETEXIMAGEPROC)get_proc("glInvalidateTexImage");
	_gl_loader_glinvalidatetexsubimage = (PFNGLINVALIDATETEXSUBIMAGEPROC)get_proc("glInvalidateTexSubImage");
	_gl_loader_glisbuffer = (PFNGLISBUFFERPROC)get_proc("glIsBuffer");
	_gl_loader_glisenabled = (PFNGLISENABLEDPROC)get_proc("glIsEnabled");
	_gl_loader_glisenabledi = (PFNGLISENABLEDIPROC)get_proc("glIsEnabledi");
	_gl_loader_glisframebuffer = (PFNGLISFRAMEBUFFERPROC)get_proc("glIsFramebuffer");
	_gl_loader_glislist = (PFNGLISLISTPROC)get_proc("glIsList");
	_gl_loader_glisprogram = (PFNGLISPROGRAMPROC)get_proc("glIsProgram");
	_gl_loader_glisprogrampipeline = (PFNGLISPROGRAMPIPELINEPROC)get_proc("glIsProgramPipeline");
	_gl_loader_glisquery = (PFNGLISQUERYPROC)get_proc("glIsQuery");
	_gl_loader_glisrenderbuffer = (PFNGLISRENDERBUFFERPROC)get_proc("glIsRenderbuffer");
	_gl_loader_glissampler = (PFNGLISSAMPLERPROC)get_proc("glIsSampler");
	_gl_loader_glisshader = (PFNGLISSHADERPROC)get_proc("glIsShader");
	_gl_loader_glissync = (PFNGLISSYNCPROC)get_proc("glIsSync");
	_gl_loader_glistexture = (PFNGLISTEXTUREPROC)get_proc("glIsTexture");
	_gl_loader_glistransformfeedback = (PFNGLISTRANSFORMFEEDBACKPROC)get_proc("glIsTransformFeedback");
	_gl_loader_glisvertexarray = (PFNGLISVERTEXARRAYPROC)get_proc("glIsVertexArray");
	_gl_loader_gllightmodelf = (PFNGLLIGHTMODELFPROC)get_proc("glLightModelf");
	_gl_loader_gllightmodelfv = (PFNGLLIGHTMODELFVPROC)get_proc("glLightModelfv");
	_gl_loader_gllightmodeli = (PFNGLLIGHTMODELIPROC)get_proc("glLightModeli");
	_gl_loader_gllightmodeliv = (PFNGLLIGHTMODELIVPROC)get_proc("glLightModeliv");
	_gl_loader_gllightf = (PFNGLLIGHTFPROC)get_proc("glLightf");
	_gl_loader_gllightfv = (PFNGLLIGHTFVPROC)get_proc("glLightfv");
	_gl_loader_gllighti = (PFNGLLIGHTIPROC)get_proc("glLighti");
	_gl_loader_gllightiv = (PFNGLLIGHTIVPROC)get_proc("glLightiv");
	_gl_loader_gllinestipple = (PFNGLLINESTIPPLEPROC)get_proc("glLineStipple");
	_gl_loader_gllinewidth = (PFNGLLINEWIDTHPROC)get_proc("glLineWidth");
	_gl_loader_gllinkprogram = (PFNGLLINKPROGRAMPROC)get_proc("glLinkProgram");
	_gl_loader_gllistbase = (PFNGLLISTBASEPROC)get_proc("glListBase");
	_gl_loader_glloadidentity = (PFNGLLOADIDENTITYPROC)get_proc("glLoadIdentity");
	_gl_loader_glloadmatrixd = (PFNGLLOADMATRIXDPROC)get_proc("glLoadMatrixd");
	_gl_loader_glloadmatrixf = (PFNGLLOADMATRIXFPROC)get_proc("glLoadMatrixf");
	_gl_loader_glloadname = (PFNGLLOADNAMEPROC)get_proc("glLoadName");
	_gl_loader_glloadtransposematrixd = (PFNGLLOADTRANSPOSEMATRIXDPROC)get_proc("glLoadTransposeMatrixd");
	_gl_loader_glloadtransposematrixf = (PFNGLLOADTRANSPOSEMATRIXFPROC)get_proc("glLoadTransposeMatrixf");
	_gl_loader_gllogicop = (PFNGLLOGICOPPROC)get_proc("glLogicOp");
	_gl_loader_glmap1d = (PFNGLMAP1DPROC)get_proc("glMap1d");
	_gl_loader_glmap1f = (PFNGLMAP1FPROC)get_proc("glMap1f");
	_gl_loader_glmap2d = (PFNGLMAP2DPROC)get_proc("glMap2d");
	_gl_loader_glmap2f = (PFNGLMAP2FPROC)get_proc("glMap2f");
	_gl_loader_glmapbuffer = (PFNGLMAPBUFFERPROC)get_proc("glMapBuffer");
	_gl_loader_glmapbufferrange = (PFNGLMAPBUFFERRANGEPROC)get_proc("glMapBufferRange");
	_gl_loader_glmapgrid1d = (PFNGLMAPGRID1DPROC)get_proc("glMapGrid1d");
	_gl_loader_glmapgrid1f = (PFNGLMAPGRID1FPROC)get_proc("glMapGrid1f");
	_gl_loader_glmapgrid2d = (PFNGLMAPGRID2DPROC)get_proc("glMapGrid2d");
	_gl_loader_glmapgrid2f = (PFNGLMAPGRID2FPROC)get_proc("glMapGrid2f");
	_gl_loader_glmapnamedbuffer = (PFNGLMAPNAMEDBUFFERPROC)get_proc("glMapNamedBuffer");
	_gl_loader_glmapnamedbufferrange = (PFNGLMAPNAMEDBUFFERRANGEPROC)get_proc("glMapNamedBufferRange");
	_gl_loader_glmaterialf = (PFNGLMATERIALFPROC)get_proc("glMaterialf");
	_gl_loader_glmaterialfv = (PFNGLMATERIALFVPROC)get_proc("glMaterialfv");
	_gl_loader_glmateriali = (PFNGLMATERIALIPROC)get_proc("glMateriali");
	_gl_loader_glmaterialiv = (PFNGLMATERIALIVPROC)get_proc("glMaterialiv");
	_gl_loader_glmatrixmode = (PFNGLMATRIXMODEPROC)get_proc("glMatrixMode");
	_gl_loader_glmemorybarrier = (PFNGLMEMORYBARRIERPROC)get_proc("glMemoryBarrier");
	_gl_loader_glmemorybarrierbyregion = (PFNGLMEMORYBARRIERBYREGIONPROC)get_proc("glMemoryBarrierByRegion");
	_gl_loader_glminsampleshading = (PFNGLMINSAMPLESHADINGPROC)get_proc("glMinSampleShading");
	_gl_loader_glmultmatrixd = (PFNGLMULTMATRIXDPROC)get_proc("glMultMatrixd");
	_gl_loader_glmultmatrixf = (PFNGLMULTMATRIXFPROC)get_proc("glMultMatrixf");
	_gl_loader_glmulttransposematrixd = (PFNGLMULTTRANSPOSEMATRIXDPROC)get_proc("glMultTransposeMatrixd");
	_gl_loader_glmulttransposematrixf = (PFNGLMULTTRANSPOSEMATRIXFPROC)get_proc("glMultTransposeMatrixf");
	_gl_loader_glmultidrawarrays = (PFNGLMULTIDRAWARRAYSPROC)get_proc("glMultiDrawArrays");
	_gl_loader_glmultidrawarraysindirect = (PFNGLMULTIDRAWARRAYSINDIRECTPROC)get_proc("glMultiDrawArraysIndirect");
	_gl_loader_glmultidrawarraysindirectcount = (PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC)get_proc("glMultiDrawArraysIndirectCount");
	_gl_loader_glmultidrawelements = (PFNGLMULTIDRAWELEMENTSPROC)get_proc("glMultiDrawElements");
	_gl_loader_glmultidrawelementsbasevertex = (PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC)get_proc("glMultiDrawElementsBaseVertex");
	_gl_loader_glmultidrawelementsindirect = (PFNGLMULTIDRAWELEMENTSINDIRECTPROC)get_proc("glMultiDrawElementsIndirect");
	_gl_loader_glmultidrawelementsindirectcount = (PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC)get_proc("glMultiDrawElementsIndirectCount");
	_gl_loader_glmultitexcoord1d = (PFNGLMULTITEXCOORD1DPROC)get_proc("glMultiTexCoord1d");
	_gl_loader_glmultitexcoord1dv = (PFNGLMULTITEXCOORD1DVPROC)get_proc("glMultiTexCoord1dv");
	_gl_loader_glmultitexcoord1f = (PFNGLMULTITEXCOORD1FPROC)get_proc("glMultiTexCoord1f");
	_gl_loader_glmultitexcoord1fv = (PFNGLMULTITEXCOORD1FVPROC)get_proc("glMultiTexCoord1fv");
	_gl_loader_glmultitexcoord1i = (PFNGLMULTITEXCOORD1IPROC)get_proc("glMultiTexCoord1i");
	_gl_loader_glmultitexcoord1iv = (PFNGLMULTITEXCOORD1IVPROC)get_proc("glMultiTexCoord1iv");
	_gl_loader_glmultitexcoord1s = (PFNGLMULTITEXCOORD1SPROC)get_proc("glMultiTexCoord1s");
	_gl_loader_glmultitexcoord1sv = (PFNGLMULTITEXCOORD1SVPROC)get_proc("glMultiTexCoord1sv");
	_gl_loader_glmultitexcoord2d = (PFNGLMULTITEXCOORD2DPROC)get_proc("glMultiTexCoord2d");
	_gl_loader_glmultitexcoord2dv = (PFNGLMULTITEXCOORD2DVPROC)get_proc("glMultiTexCoord2dv");
	_gl_loader_glmultitexcoord2f = (PFNGLMULTITEXCOORD2FPROC)get_proc("glMultiTexCoord2f");
	_gl_loader_glmultitexcoord2fv = (PFNGLMULTITEXCOORD2FVPROC)get_proc("glMultiTexCoord2fv");
	_gl_loader_glmultitexcoord2i = (PFNGLMULTITEXCOORD2IPROC)get_proc("glMultiTexCoord2i");
	_gl_loader_glmultitexcoord2iv = (PFNGLMULTITEXCOORD2IVPROC)get_proc("glMultiTexCoord2iv");
	_gl_loader_glmultitexcoord2s = (PFNGLMULTITEXCOORD2SPROC)get_proc("glMultiTexCoord2s");
	_gl_loader_glmultitexcoord2sv = (PFNGLMULTITEXCOORD2SVPROC)get_proc("glMultiTexCoord2sv");
	_gl_loader_glmultitexcoord3d = (PFNGLMULTITEXCOORD3DPROC)get_proc("glMultiTexCoord3d");
	_gl_loader_glmultitexcoord3dv = (PFNGLMULTITEXCOORD3DVPROC)get_proc("glMultiTexCoord3dv");
	_gl_loader_glmultitexcoord3f = (PFNGLMULTITEXCOORD3FPROC)get_proc("glMultiTexCoord3f");
	_gl_loader_glmultitexcoord3fv = (PFNGLMULTITEXCOORD3FVPROC)get_proc("glMultiTexCoord3fv");
	_gl_loader_glmultitexcoord3i = (PFNGLMULTITEXCOORD3IPROC)get_proc("glMultiTexCoord3i");
	_gl_loader_glmultitexcoord3iv = (PFNGLMULTITEXCOORD3IVPROC)get_proc("glMultiTexCoord3iv");
	_gl_loader_glmultitexcoord3s = (PFNGLMULTITEXCOORD3SPROC)get_proc("glMultiTexCoord3s");
	_gl_loader_glmultitexcoord3sv = (PFNGLMULTITEXCOORD3SVPROC)get_proc("glMultiTexCoord3sv");
	_gl_loader_glmultitexcoord4d = (PFNGLMULTITEXCOORD4DPROC)get_proc("glMultiTexCoord4d");
	_gl_loader_glmultitexcoord4dv = (PFNGLMULTITEXCOORD4DVPROC)get_proc("glMultiTexCoord4dv");
	_gl_loader_glmultitexcoord4f = (PFNGLMULTITEXCOORD4FPROC)get_proc("glMultiTexCoord4f");
	_gl_loader_glmultitexcoord4fv = (PFNGLMULTITEXCOORD4FVPROC)get_proc("glMultiTexCoord4fv");
	_gl_loader_glmultitexcoord4i = (PFNGLMULTITEXCOORD4IPROC)get_proc("glMultiTexCoord4i");
	_gl_loader_glmultitexcoord4iv = (PFNGLMULTITEXCOORD4IVPROC)get_proc("glMultiTexCoord4iv");
	_gl_loader_glmultitexcoord4s = (PFNGLMULTITEXCOORD4SPROC)get_proc("glMultiTexCoord4s");
	_gl_loader_glmultitexcoord4sv = (PFNGLMULTITEXCOORD4SVPROC)get_proc("glMultiTexCoord4sv");
	_gl_loader_glmultitexcoordp1ui = (PFNGLMULTITEXCOORDP1UIPROC)get_proc("glMultiTexCoordP1ui");
	_gl_loader_glmultitexcoordp1uiv = (PFNGLMULTITEXCOORDP1UIVPROC)get_proc("glMultiTexCoordP1uiv");
	_gl_loader_glmultitexcoordp2ui = (PFNGLMULTITEXCOORDP2UIPROC)get_proc("glMultiTexCoordP2ui");
	_gl_loader_glmultitexcoordp2uiv = (PFNGLMULTITEXCOORDP2UIVPROC)get_proc("glMultiTexCoordP2uiv");
	_gl_loader_glmultitexcoordp3ui = (PFNGLMULTITEXCOORDP3UIPROC)get_proc("glMultiTexCoordP3ui");
	_gl_loader_glmultitexcoordp3uiv = (PFNGLMULTITEXCOORDP3UIVPROC)get_proc("glMultiTexCoordP3uiv");
	_gl_loader_glmultitexcoordp4ui = (PFNGLMULTITEXCOORDP4UIPROC)get_proc("glMultiTexCoordP4ui");
	_gl_loader_glmultitexcoordp4uiv = (PFNGLMULTITEXCOORDP4UIVPROC)get_proc("glMultiTexCoordP4uiv");
	_gl_loader_glnamedbufferdata = (PFNGLNAMEDBUFFERDATAPROC)get_proc("glNamedBufferData");
	_gl_loader_glnamedbufferstorage = (PFNGLNAMEDBUFFERSTORAGEPROC)get_proc("glNamedBufferStorage");
	_gl_loader_glnamedbuffersubdata = (PFNGLNAMEDBUFFERSUBDATAPROC)get_proc("glNamedBufferSubData");
	_gl_loader_glnamedframebufferdrawbuffer = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC)get_proc("glNamedFramebufferDrawBuffer");
	_gl_loader_glnamedframebufferdrawbuffers = (PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC)get_proc("glNamedFramebufferDrawBuffers");
	_gl_loader_glnamedframebufferparameteri = (PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC)get_proc("glNamedFramebufferParameteri");
	_gl_loader_glnamedframebufferreadbuffer = (PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC)get_proc("glNamedFramebufferReadBuffer");
	_gl_loader_glnamedframebufferrenderbuffer = (PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC)get_proc("glNamedFramebufferRenderbuffer");
	_gl_loader_glnamedframebuffertexture = (PFNGLNAMEDFRAMEBUFFERTEXTUREPROC)get_proc("glNamedFramebufferTexture");
	_gl_loader_glnamedframebuffertexturelayer = (PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC)get_proc("glNamedFramebufferTextureLayer");
	_gl_loader_glnamedrenderbufferstorage = (PFNGLNAMEDRENDERBUFFERSTORAGEPROC)get_proc("glNamedRenderbufferStorage");
	_gl_loader_glnamedrenderbufferstoragemultisample = (PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC)get_proc("glNamedRenderbufferStorageMultisample");
	_gl_loader_glnewlist = (PFNGLNEWLISTPROC)get_proc("glNewList");
	_gl_loader_glnormal3b = (PFNGLNORMAL3BPROC)get_proc("glNormal3b");
	_gl_loader_glnormal3bv = (PFNGLNORMAL3BVPROC)get_proc("glNormal3bv");
	_gl_loader_glnormal3d = (PFNGLNORMAL3DPROC)get_proc("glNormal3d");
	_gl_loader_glnormal3dv = (PFNGLNORMAL3DVPROC)get_proc("glNormal3dv");
	_gl_loader_glnormal3f = (PFNGLNORMAL3FPROC)get_proc("glNormal3f");
	_gl_loader_glnormal3fv = (PFNGLNORMAL3FVPROC)get_proc("glNormal3fv");
	_gl_loader_glnormal3i = (PFNGLNORMAL3IPROC)get_proc("glNormal3i");
	_gl_loader_glnormal3iv = (PFNGLNORMAL3IVPROC)get_proc("glNormal3iv");
	_gl_loader_glnormal3s = (PFNGLNORMAL3SPROC)get_proc("glNormal3s");
	_gl_loader_glnormal3sv = (PFNGLNORMAL3SVPROC)get_proc("glNormal3sv");
	_gl_loader_glnormalp3ui = (PFNGLNORMALP3UIPROC)get_proc("glNormalP3ui");
	_gl_loader_glnormalp3uiv = (PFNGLNORMALP3UIVPROC)get_proc("glNormalP3uiv");
	_gl_loader_glnormalpointer = (PFNGLNORMALPOINTERPROC)get_proc("glNormalPointer");
	_gl_loader_globjectlabel = (PFNGLOBJECTLABELPROC)get_proc("glObjectLabel");
	_gl_loader_globjectptrlabel = (PFNGLOBJECTPTRLABELPROC)get_proc("glObjectPtrLabel");
	_gl_loader_glortho = (PFNGLORTHOPROC)get_proc("glOrtho");
	_gl_loader_glpassthrough = (PFNGLPASSTHROUGHPROC)get_proc("glPassThrough");
	_gl_loader_glpatchparameterfv = (PFNGLPATCHPARAMETERFVPROC)get_proc("glPatchParameterfv");
	_gl_loader_glpatchparameteri = (PFNGLPATCHPARAMETERIPROC)get_proc("glPatchParameteri");
	_gl_loader_glpausetransformfeedback = (PFNGLPAUSETRANSFORMFEEDBACKPROC)get_proc("glPauseTransformFeedback");
	_gl_loader_glpixelmapfv = (PFNGLPIXELMAPFVPROC)get_proc("glPixelMapfv");
	_gl_loader_glpixelmapuiv = (PFNGLPIXELMAPUIVPROC)get_proc("glPixelMapuiv");
	_gl_loader_glpixelmapusv = (PFNGLPIXELMAPUSVPROC)get_proc("glPixelMapusv");
	_gl_loader_glpixelstoref = (PFNGLPIXELSTOREFPROC)get_proc("glPixelStoref");
	_gl_loader_glpixelstorei = (PFNGLPIXELSTOREIPROC)get_proc("glPixelStorei");
	_gl_loader_glpixeltransferf = (PFNGLPIXELTRANSFERFPROC)get_proc("glPixelTransferf");
	_gl_loader_glpixeltransferi = (PFNGLPIXELTRANSFERIPROC)get_proc("glPixelTransferi");
	_gl_loader_glpixelzoom = (PFNGLPIXELZOOMPROC)get_proc("glPixelZoom");
	_gl_loader_glpointparameterf = (PFNGLPOINTPARAMETERFPROC)get_proc("glPointParameterf");
	_gl_loader_glpointparameterfv = (PFNGLPOINTPARAMETERFVPROC)get_proc("glPointParameterfv");
	_gl_loader_glpointparameteri = (PFNGLPOINTPARAMETERIPROC)get_proc("glPointParameteri");
	_gl_loader_glpointparameteriv = (PFNGLPOINTPARAMETERIVPROC)get_proc("glPointParameteriv");
	_gl_loader_glpointsize = (PFNGLPOINTSIZEPROC)get_proc("glPointSize");
	_gl_loader_glpolygonmode = (PFNGLPOLYGONMODEPROC)get_proc("glPolygonMode");
	_gl_loader_glpolygonoffset = (PFNGLPOLYGONOFFSETPROC)get_proc("glPolygonOffset");
	_gl_loader_glpolygonoffsetclamp = (PFNGLPOLYGONOFFSETCLAMPPROC)get_proc("glPolygonOffsetClamp");
	_gl_loader_glpolygonstipple = (PFNGLPOLYGONSTIPPLEPROC)get_proc("glPolygonStipple");
	_gl_loader_glpopattrib = (PFNGLPOPATTRIBPROC)get_proc("glPopAttrib");
	_gl_loader_glpopclientattrib = (PFNGLPOPCLIENTATTRIBPROC)get_proc("glPopClientAttrib");
	_gl_loader_glpopdebuggroup = (PFNGLPOPDEBUGGROUPPROC)get_proc("glPopDebugGroup");
	_gl_loader_glpopmatrix = (PFNGLPOPMATRIXPROC)get_proc("glPopMatrix");
	_gl_loader_glpopname = (PFNGLPOPNAMEPROC)get_proc("glPopName");
	_gl_loader_glprimitiverestartindex = (PFNGLPRIMITIVERESTARTINDEXPROC)get_proc("glPrimitiveRestartIndex");
	_gl_loader_glprioritizetextures = (PFNGLPRIORITIZETEXTURESPROC)get_proc("glPrioritizeTextures");
	_gl_loader_glprogrambinary = (PFNGLPROGRAMBINARYPROC)get_proc("glProgramBinary");
	_gl_loader_glprogramparameteri = (PFNGLPROGRAMPARAMETERIPROC)get_proc("glProgramParameteri");
	_gl_loader_glprogramuniform1d = (PFNGLPROGRAMUNIFORM1DPROC)get_proc("glProgramUniform1d");
	_gl_loader_glprogramuniform1dv = (PFNGLPROGRAMUNIFORM1DVPROC)get_proc("glProgramUniform1dv");
	_gl_loader_glprogramuniform1f = (PFNGLPROGRAMUNIFORM1FPROC)get_proc("glProgramUniform1f");
	_gl_loader_glprogramuniform1fv = (PFNGLPROGRAMUNIFORM1FVPROC)get_proc("glProgramUniform1fv");
	_gl_loader_glprogramuniform1i = (PFNGLPROGRAMUNIFORM1IPROC)get_proc("glProgramUniform1i");
	_gl_loader_glprogramuniform1iv = (PFNGLPROGRAMUNIFORM1IVPROC)get_proc("glProgramUniform1iv");
	_gl_loader_glprogramuniform1ui = (PFNGLPROGRAMUNIFORM1UIPROC)get_proc("glProgramUniform1ui");
	_gl_loader_glprogramuniform1uiv = (PFNGLPROGRAMUNIFORM1UIVPROC)get_proc("glProgramUniform1uiv");
	_gl_loader_glprogramuniform2d = (PFNGLPROGRAMUNIFORM2DPROC)get_proc("glProgramUniform2d");
	_gl_loader_glprogramuniform2dv = (PFNGLPROGRAMUNIFORM2DVPROC)get_proc("glProgramUniform2dv");
	_gl_loader_glprogramuniform2f = (PFNGLPROGRAMUNIFORM2FPROC)get_proc("glProgramUniform2f");
	_gl_loader_glprogramuniform2fv = (PFNGLPROGRAMUNIFORM2FVPROC)get_proc("glProgramUniform2fv");
	_gl_loader_glprogramuniform2i = (PFNGLPROGRAMUNIFORM2IPROC)get_proc("glProgramUniform2i");
	_gl_loader_glprogramuniform2iv = (PFNGLPROGRAMUNIFORM2IVPROC)get_proc("glProgramUniform2iv");
	_gl_loader_glprogramuniform2ui = (PFNGLPROGRAMUNIFORM2UIPROC)get_proc("glProgramUniform2ui");
	_gl_loader_glprogramuniform2uiv = (PFNGLPROGRAMUNIFORM2UIVPROC)get_proc("glProgramUniform2uiv");
	_gl_loader_glprogramuniform3d = (PFNGLPROGRAMUNIFORM3DPROC)get_proc("glProgramUniform3d");
	_gl_loader_glprogramuniform3dv = (PFNGLPROGRAMUNIFORM3DVPROC)get_proc("glProgramUniform3dv");
	_gl_loader_glprogramuniform3f = (PFNGLPROGRAMUNIFORM3FPROC)get_proc("glProgramUniform3f");
	_gl_loader_glprogramuniform3fv = (PFNGLPROGRAMUNIFORM3FVPROC)get_proc("glProgramUniform3fv");
	_gl_loader_glprogramuniform3i = (PFNGLPROGRAMUNIFORM3IPROC)get_proc("glProgramUniform3i");
	_gl_loader_glprogramuniform3iv = (PFNGLPROGRAMUNIFORM3IVPROC)get_proc("glProgramUniform3iv");
	_gl_loader_glprogramuniform3ui = (PFNGLPROGRAMUNIFORM3UIPROC)get_proc("glProgramUniform3ui");
	_gl_loader_glprogramuniform3uiv = (PFNGLPROGRAMUNIFORM3UIVPROC)get_proc("glProgramUniform3uiv");
	_gl_loader_glprogramuniform4d = (PFNGLPROGRAMUNIFORM4DPROC)get_proc("glProgramUniform4d");
	_gl_loader_glprogramuniform4dv = (PFNGLPROGRAMUNIFORM4DVPROC)get_proc("glProgramUniform4dv");
	_gl_loader_glprogramuniform4f = (PFNGLPROGRAMUNIFORM4FPROC)get_proc("glProgramUniform4f");
	_gl_loader_glprogramuniform4fv = (PFNGLPROGRAMUNIFORM4FVPROC)get_proc("glProgramUniform4fv");
	_gl_loader_glprogramuniform4i = (PFNGLPROGRAMUNIFORM4IPROC)get_proc("glProgramUniform4i");
	_gl_loader_glprogramuniform4iv = (PFNGLPROGRAMUNIFORM4IVPROC)get_proc("glProgramUniform4iv");
	_gl_loader_glprogramuniform4ui = (PFNGLPROGRAMUNIFORM4UIPROC)get_proc("glProgramUniform4ui");
	_gl_loader_glprogramuniform4uiv = (PFNGLPROGRAMUNIFORM4UIVPROC)get_proc("glProgramUniform4uiv");
	_gl_loader_glprogramuniformmatrix2dv = (PFNGLPROGRAMUNIFORMMATRIX2DVPROC)get_proc("glProgramUniformMatrix2dv");
	_gl_loader_glprogramuniformmatrix2fv = (PFNGLPROGRAMUNIFORMMATRIX2FVPROC)get_proc("glProgramUniformMatrix2fv");
	_gl_loader_glprogramuniformmatrix2x3dv = (PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC)get_proc("glProgramUniformMatrix2x3dv");
	_gl_loader_glprogramuniformmatrix2x3fv = (PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC)get_proc("glProgramUniformMatrix2x3fv");
	_gl_loader_glprogramuniformmatrix2x4dv = (PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC)get_proc("glProgramUniformMatrix2x4dv");
	_gl_loader_glprogramuniformmatrix2x4fv = (PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC)get_proc("glProgramUniformMatrix2x4fv");
	_gl_loader_glprogramuniformmatrix3dv = (PFNGLPROGRAMUNIFORMMATRIX3DVPROC)get_proc("glProgramUniformMatrix3dv");
	_gl_loader_glprogramuniformmatrix3fv = (PFNGLPROGRAMUNIFORMMATRIX3FVPROC)get_proc("glProgramUniformMatrix3fv");
	_gl_loader_glprogramuniformmatrix3x2dv = (PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC)get_proc("glProgramUniformMatrix3x2dv");
	_gl_loader_glprogramuniformmatrix3x2fv = (PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC)get_proc("glProgramUniformMatrix3x2fv");
	_gl_loader_glprogramuniformmatrix3x4dv = (PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC)get_proc("glProgramUniformMatrix3x4dv");
	_gl_loader_glprogramuniformmatrix3x4fv = (PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC)get_proc("glProgramUniformMatrix3x4fv");
	_gl_loader_glprogramuniformmatrix4dv = (PFNGLPROGRAMUNIFORMMATRIX4DVPROC)get_proc("glProgramUniformMatrix4dv");
	_gl_loader_glprogramuniformmatrix4fv = (PFNGLPROGRAMUNIFORMMATRIX4FVPROC)get_proc("glProgramUniformMatrix4fv");
	_gl_loader_glprogramuniformmatrix4x2dv = (PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC)get_proc("glProgramUniformMatrix4x2dv");
	_gl_loader_glprogramuniformmatrix4x2fv = (PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC)get_proc("glProgramUniformMatrix4x2fv");
	_gl_loader_glprogramuniformmatrix4x3dv = (PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC)get_proc("glProgramUniformMatrix4x3dv");
	_gl_loader_glprogramuniformmatrix4x3fv = (PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC)get_proc("glProgramUniformMatrix4x3fv");
	_gl_loader_glprovokingvertex = (PFNGLPROVOKINGVERTEXPROC)get_proc("glProvokingVertex");
	_gl_loader_glpushattrib = (PFNGLPUSHATTRIBPROC)get_proc("glPushAttrib");
	_gl_loader_glpushclientattrib = (PFNGLPUSHCLIENTATTRIBPROC)get_proc("glPushClientAttrib");
	_gl_loader_glpushdebuggroup = (PFNGLPUSHDEBUGGROUPPROC)get_proc("glPushDebugGroup");
	_gl_loader_glpushmatrix = (PFNGLPUSHMATRIXPROC)get_proc("glPushMatrix");
	_gl_loader_glpushname = (PFNGLPUSHNAMEPROC)get_proc("glPushName");
	_gl_loader_glquerycounter = (PFNGLQUERYCOUNTERPROC)get_proc("glQueryCounter");
	_gl_loader_glrasterpos2d = (PFNGLRASTERPOS2DPROC)get_proc("glRasterPos2d");
	_gl_loader_glrasterpos2dv = (PFNGLRASTERPOS2DVPROC)get_proc("glRasterPos2dv");
	_gl_loader_glrasterpos2f = (PFNGLRASTERPOS2FPROC)get_proc("glRasterPos2f");
	_gl_loader_glrasterpos2fv = (PFNGLRASTERPOS2FVPROC)get_proc("glRasterPos2fv");
	_gl_loader_glrasterpos2i = (PFNGLRASTERPOS2IPROC)get_proc("glRasterPos2i");
	_gl_loader_glrasterpos2iv = (PFNGLRASTERPOS2IVPROC)get_proc("glRasterPos2iv");
	_gl_loader_glrasterpos2s = (PFNGLRASTERPOS2SPROC)get_proc("glRasterPos2s");
	_gl_loader_glrasterpos2sv = (PFNGLRASTERPOS2SVPROC)get_proc("glRasterPos2sv");
	_gl_loader_glrasterpos3d = (PFNGLRASTERPOS3DPROC)get_proc("glRasterPos3d");
	_gl_loader_glrasterpos3dv = (PFNGLRASTERPOS3DVPROC)get_proc("glRasterPos3dv");
	_gl_loader_glrasterpos3f = (PFNGLRASTERPOS3FPROC)get_proc("glRasterPos3f");
	_gl_loader_glrasterpos3fv = (PFNGLRASTERPOS3FVPROC)get_proc("glRasterPos3fv");
	_gl_loader_glrasterpos3i = (PFNGLRASTERPOS3IPROC)get_proc("glRasterPos3i");
	_gl_loader_glrasterpos3iv = (PFNGLRASTERPOS3IVPROC)get_proc("glRasterPos3iv");
	_gl_loader_glrasterpos3s = (PFNGLRASTERPOS3SPROC)get_proc("glRasterPos3s");
	_gl_loader_glrasterpos3sv = (PFNGLRASTERPOS3SVPROC)get_proc("glRasterPos3sv");
	_gl_loader_glrasterpos4d = (PFNGLRASTERPOS4DPROC)get_proc("glRasterPos4d");
	_gl_loader_glrasterpos4dv = (PFNGLRASTERPOS4DVPROC)get_proc("glRasterPos4dv");
	_gl_loader_glrasterpos4f = (PFNGLRASTERPOS4FPROC)get_proc("glRasterPos4f");
	_gl_loader_glrasterpos4fv = (PFNGLRASTERPOS4FVPROC)get_proc("glRasterPos4fv");
	_gl_loader_glrasterpos4i = (PFNGLRASTERPOS4IPROC)get_proc("glRasterPos4i");
	_gl_loader_glrasterpos4iv = (PFNGLRASTERPOS4IVPROC)get_proc("glRasterPos4iv");
	_gl_loader_glrasterpos4s = (PFNGLRASTERPOS4SPROC)get_proc("glRasterPos4s");
	_gl_loader_glrasterpos4sv = (PFNGLRASTERPOS4SVPROC)get_proc("glRasterPos4sv");
	_gl_loader_glreadbuffer = (PFNGLREADBUFFERPROC)get_proc("glReadBuffer");
	_gl_loader_glreadpixels = (PFNGLREADPIXELSPROC)get_proc("glReadPixels");
	_gl_loader_glreadnpixels = (PFNGLREADNPIXELSPROC)get_proc("glReadnPixels");
	_gl_loader_glrectd = (PFNGLRECTDPROC)get_proc("glRectd");
	_gl_loader_glrectdv = (PFNGLRECTDVPROC)get_proc("glRectdv");
	_gl_loader_glrectf = (PFNGLRECTFPROC)get_proc("glRectf");
	_gl_loader_glrectfv = (PFNGLRECTFVPROC)get_proc("glRectfv");
	_gl_loader_glrecti = (PFNGLRECTIPROC)get_proc("glRecti");
	_gl_loader_glrectiv = (PFNGLRECTIVPROC)get_proc("glRectiv");
	_gl_loader_glrects = (PFNGLRECTSPROC)get_proc("glRects");
	_gl_loader_glrectsv = (PFNGLRECTSVPROC)get_proc("glRectsv");
	_gl_loader_glreleaseshadercompiler = (PFNGLRELEASESHADERCOMPILERPROC)get_proc("glReleaseShaderCompiler");
	_gl_loader_glrendermode = (PFNGLRENDERMODEPROC)get_proc("glRenderMode");
	_gl_loader_glrenderbufferstorage = (PFNGLRENDERBUFFERSTORAGEPROC)get_proc("glRenderbufferStorage");
	_gl_loader_glrenderbufferstoragemultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)get_proc("glRenderbufferStorageMultisample");
	_gl_loader_glresumetransformfeedback = (PFNGLRESUMETRANSFORMFEEDBACKPROC)get_proc("glResumeTransformFeedback");
	_gl_loader_glrotated = (PFNGLROTATEDPROC)get_proc("glRotated");
	_gl_loader_glrotatef = (PFNGLROTATEFPROC)get_proc("glRotatef");
	_gl_loader_glsamplecoverage = (PFNGLSAMPLECOVERAGEPROC)get_proc("glSampleCoverage");
	_gl_loader_glsamplemaski = (PFNGLSAMPLEMASKIPROC)get_proc("glSampleMaski");
	_gl_loader_glsamplerparameteriiv = (PFNGLSAMPLERPARAMETERIIVPROC)get_proc("glSamplerParameterIiv");
	_gl_loader_glsamplerparameteriuiv = (PFNGLSAMPLERPARAMETERIUIVPROC)get_proc("glSamplerParameterIuiv");
	_gl_loader_glsamplerparameterf = (PFNGLSAMPLERPARAMETERFPROC)get_proc("glSamplerParameterf");
	_gl_loader_glsamplerparameterfv = (PFNGLSAMPLERPARAMETERFVPROC)get_proc("glSamplerParameterfv");
	_gl_loader_glsamplerparameteri = (PFNGLSAMPLERPARAMETERIPROC)get_proc("glSamplerParameteri");
	_gl_loader_glsamplerparameteriv = (PFNGLSAMPLERPARAMETERIVPROC)get_proc("glSamplerParameteriv");
	_gl_loader_glscaled = (PFNGLSCALEDPROC)get_proc("glScaled");
	_gl_loader_glscalef = (PFNGLSCALEFPROC)get_proc("glScalef");
	_gl_loader_glscissor = (PFNGLSCISSORPROC)get_proc("glScissor");
	_gl_loader_glscissorarrayv = (PFNGLSCISSORARRAYVPROC)get_proc("glScissorArrayv");
	_gl_loader_glscissorindexed = (PFNGLSCISSORINDEXEDPROC)get_proc("glScissorIndexed");
	_gl_loader_glscissorindexedv = (PFNGLSCISSORINDEXEDVPROC)get_proc("glScissorIndexedv");
	_gl_loader_glsecondarycolor3b = (PFNGLSECONDARYCOLOR3BPROC)get_proc("glSecondaryColor3b");
	_gl_loader_glsecondarycolor3bv = (PFNGLSECONDARYCOLOR3BVPROC)get_proc("glSecondaryColor3bv");
	_gl_loader_glsecondarycolor3d = (PFNGLSECONDARYCOLOR3DPROC)get_proc("glSecondaryColor3d");
	_gl_loader_glsecondarycolor3dv = (PFNGLSECONDARYCOLOR3DVPROC)get_proc("glSecondaryColor3dv");
	_gl_loader_glsecondarycolor3f = (PFNGLSECONDARYCOLOR3FPROC)get_proc("glSecondaryColor3f");
	_gl_loader_glsecondarycolor3fv = (PFNGLSECONDARYCOLOR3FVPROC)get_proc("glSecondaryColor3fv");
	_gl_loader_glsecondarycolor3i = (PFNGLSECONDARYCOLOR3IPROC)get_proc("glSecondaryColor3i");
	_gl_loader_glsecondarycolor3iv = (PFNGLSECONDARYCOLOR3IVPROC)get_proc("glSecondaryColor3iv");
	_gl_loader_glsecondarycolor3s = (PFNGLSECONDARYCOLOR3SPROC)get_proc("glSecondaryColor3s");
	_gl_loader_glsecondarycolor3sv = (PFNGLSECONDARYCOLOR3SVPROC)get_proc("glSecondaryColor3sv");
	_gl_loader_glsecondarycolor3ub = (PFNGLSECONDARYCOLOR3UBPROC)get_proc("glSecondaryColor3ub");
	_gl_loader_glsecondarycolor3ubv = (PFNGLSECONDARYCOLOR3UBVPROC)get_proc("glSecondaryColor3ubv");
	_gl_loader_glsecondarycolor3ui = (PFNGLSECONDARYCOLOR3UIPROC)get_proc("glSecondaryColor3ui");
	_gl_loader_glsecondarycolor3uiv = (PFNGLSECONDARYCOLOR3UIVPROC)get_proc("glSecondaryColor3uiv");
	_gl_loader_glsecondarycolor3us = (PFNGLSECONDARYCOLOR3USPROC)get_proc("glSecondaryColor3us");
	_gl_loader_glsecondarycolor3usv = (PFNGLSECONDARYCOLOR3USVPROC)get_proc("glSecondaryColor3usv");
	_gl_loader_glsecondarycolorp3ui = (PFNGLSECONDARYCOLORP3UIPROC)get_proc("glSecondaryColorP3ui");
	_gl_loader_glsecondarycolorp3uiv = (PFNGLSECONDARYCOLORP3UIVPROC)get_proc("glSecondaryColorP3uiv");
	_gl_loader_glsecondarycolorpointer = (PFNGLSECONDARYCOLORPOINTERPROC)get_proc("glSecondaryColorPointer");
	_gl_loader_glselectbuffer = (PFNGLSELECTBUFFERPROC)get_proc("glSelectBuffer");
	_gl_loader_glshademodel = (PFNGLSHADEMODELPROC)get_proc("glShadeModel");
	_gl_loader_glshaderbinary = (PFNGLSHADERBINARYPROC)get_proc("glShaderBinary");
	_gl_loader_glshadersource = (PFNGLSHADERSOURCEPROC)get_proc("glShaderSource");
	_gl_loader_glshaderstorageblockbinding = (PFNGLSHADERSTORAGEBLOCKBINDINGPROC)get_proc("glShaderStorageBlockBinding");
	_gl_loader_glspecializeshader = (PFNGLSPECIALIZESHADERPROC)get_proc("glSpecializeShader");
	_gl_loader_glstencilfunc = (PFNGLSTENCILFUNCPROC)get_proc("glStencilFunc");
	_gl_loader_glstencilfuncseparate = (PFNGLSTENCILFUNCSEPARATEPROC)get_proc("glStencilFuncSeparate");
	_gl_loader_glstencilmask = (PFNGLSTENCILMASKPROC)get_proc("glStencilMask");
	_gl_loader_glstencilmaskseparate = (PFNGLSTENCILMASKSEPARATEPROC)get_proc("glStencilMaskSeparate");
	_gl_loader_glstencilop = (PFNGLSTENCILOPPROC)get_proc("glStencilOp");
	_gl_loader_glstencilopseparate = (PFNGLSTENCILOPSEPARATEPROC)get_proc("glStencilOpSeparate");
	_gl_loader_gltexbuffer = (PFNGLTEXBUFFERPROC)get_proc("glTexBuffer");
	_gl_loader_gltexbufferrange = (PFNGLTEXBUFFERRANGEPROC)get_proc("glTexBufferRange");
	_gl_loader_gltexcoord1d = (PFNGLTEXCOORD1DPROC)get_proc("glTexCoord1d");
	_gl_loader_gltexcoord1dv = (PFNGLTEXCOORD1DVPROC)get_proc("glTexCoord1dv");
	_gl_loader_gltexcoord1f = (PFNGLTEXCOORD1FPROC)get_proc("glTexCoord1f");
	_gl_loader_gltexcoord1fv = (PFNGLTEXCOORD1FVPROC)get_proc("glTexCoord1fv");
	_gl_loader_gltexcoord1i = (PFNGLTEXCOORD1IPROC)get_proc("glTexCoord1i");
	_gl_loader_gltexcoord1iv = (PFNGLTEXCOORD1IVPROC)get_proc("glTexCoord1iv");
	_gl_loader_gltexcoord1s = (PFNGLTEXCOORD1SPROC)get_proc("glTexCoord1s");
	_gl_loader_gltexcoord1sv = (PFNGLTEXCOORD1SVPROC)get_proc("glTexCoord1sv");
	_gl_loader_gltexcoord2d = (PFNGLTEXCOORD2DPROC)get_proc("glTexCoord2d");
	_gl_loader_gltexcoord2dv = (PFNGLTEXCOORD2DVPROC)get_proc("glTexCoord2dv");
	_gl_loader_gltexcoord2f = (PFNGLTEXCOORD2FPROC)get_proc("glTexCoord2f");
	_gl_loader_gltexcoord2fv = (PFNGLTEXCOORD2FVPROC)get_proc("glTexCoord2fv");
	_gl_loader_gltexcoord2i = (PFNGLTEXCOORD2IPROC)get_proc("glTexCoord2i");
	_gl_loader_gltexcoord2iv = (PFNGLTEXCOORD2IVPROC)get_proc("glTexCoord2iv");
	_gl_loader_gltexcoord2s = (PFNGLTEXCOORD2SPROC)get_proc("glTexCoord2s");
	_gl_loader_gltexcoord2sv = (PFNGLTEXCOORD2SVPROC)get_proc("glTexCoord2sv");
	_gl_loader_gltexcoord3d = (PFNGLTEXCOORD3DPROC)get_proc("glTexCoord3d");
	_gl_loader_gltexcoord3dv = (PFNGLTEXCOORD3DVPROC)get_proc("glTexCoord3dv");
	_gl_loader_gltexcoord3f = (PFNGLTEXCOORD3FPROC)get_proc("glTexCoord3f");
	_gl_loader_gltexcoord3fv = (PFNGLTEXCOORD3FVPROC)get_proc("glTexCoord3fv");
	_gl_loader_gltexcoord3i = (PFNGLTEXCOORD3IPROC)get_proc("glTexCoord3i");
	_gl_loader_gltexcoord3iv = (PFNGLTEXCOORD3IVPROC)get_proc("glTexCoord3iv");
	_gl_loader_gltexcoord3s = (PFNGLTEXCOORD3SPROC)get_proc("glTexCoord3s");
	_gl_loader_gltexcoord3sv = (PFNGLTEXCOORD3SVPROC)get_proc("glTexCoord3sv");
	_gl_loader_gltexcoord4d = (PFNGLTEXCOORD4DPROC)get_proc("glTexCoord4d");
	_gl_loader_gltexcoord4dv = (PFNGLTEXCOORD4DVPROC)get_proc("glTexCoord4dv");
	_gl_loader_gltexcoord4f = (PFNGLTEXCOORD4FPROC)get_proc("glTexCoord4f");
	_gl_loader_gltexcoord4fv = (PFNGLTEXCOORD4FVPROC)get_proc("glTexCoord4fv");
	_gl_loader_gltexcoord4i = (PFNGLTEXCOORD4IPROC)get_proc("glTexCoord4i");
	_gl_loader_gltexcoord4iv = (PFNGLTEXCOORD4IVPROC)get_proc("glTexCoord4iv");
	_gl_loader_gltexcoord4s = (PFNGLTEXCOORD4SPROC)get_proc("glTexCoord4s");
	_gl_loader_gltexcoord4sv = (PFNGLTEXCOORD4SVPROC)get_proc("glTexCoord4sv");
	_gl_loader_gltexcoordp1ui = (PFNGLTEXCOORDP1UIPROC)get_proc("glTexCoordP1ui");
	_gl_loader_gltexcoordp1uiv = (PFNGLTEXCOORDP1UIVPROC)get_proc("glTexCoordP1uiv");
	_gl_loader_gltexcoordp2ui = (PFNGLTEXCOORDP2UIPROC)get_proc("glTexCoordP2ui");
	_gl_loader_gltexcoordp2uiv = (PFNGLTEXCOORDP2UIVPROC)get_proc("glTexCoordP2uiv");
	_gl_loader_gltexcoordp3ui = (PFNGLTEXCOORDP3UIPROC)get_proc("glTexCoordP3ui");
	_gl_loader_gltexcoordp3uiv = (PFNGLTEXCOORDP3UIVPROC)get_proc("glTexCoordP3uiv");
	_gl_loader_gltexcoordp4ui = (PFNGLTEXCOORDP4UIPROC)get_proc("glTexCoordP4ui");
	_gl_loader_gltexcoordp4uiv = (PFNGLTEXCOORDP4UIVPROC)get_proc("glTexCoordP4uiv");
	_gl_loader_gltexcoordpointer = (PFNGLTEXCOORDPOINTERPROC)get_proc("glTexCoordPointer");
	_gl_loader_gltexenvf = (PFNGLTEXENVFPROC)get_proc("glTexEnvf");
	_gl_loader_gltexenvfv = (PFNGLTEXENVFVPROC)get_proc("glTexEnvfv");
	_gl_loader_gltexenvi = (PFNGLTEXENVIPROC)get_proc("glTexEnvi");
	_gl_loader_gltexenviv = (PFNGLTEXENVIVPROC)get_proc("glTexEnviv");
	_gl_loader_gltexgend = (PFNGLTEXGENDPROC)get_proc("glTexGend");
	_gl_loader_gltexgendv = (PFNGLTEXGENDVPROC)get_proc("glTexGendv");
	_gl_loader_gltexgenf = (PFNGLTEXGENFPROC)get_proc("glTexGenf");
	_gl_loader_gltexgenfv = (PFNGLTEXGENFVPROC)get_proc("glTexGenfv");
	_gl_loader_gltexgeni = (PFNGLTEXGENIPROC)get_proc("glTexGeni");
	_gl_loader_gltexgeniv = (PFNGLTEXGENIVPROC)get_proc("glTexGeniv");
	_gl_loader_glteximage1d = (PFNGLTEXIMAGE1DPROC)get_proc("glTexImage1D");
	_gl_loader_glteximage2d = (PFNGLTEXIMAGE2DPROC)get_proc("glTexImage2D");
	_gl_loader_glteximage2dmultisample = (PFNGLTEXIMAGE2DMULTISAMPLEPROC)get_proc("glTexImage2DMultisample");
	_gl_loader_glteximage3d = (PFNGLTEXIMAGE3DPROC)get_proc("glTexImage3D");
	_gl_loader_glteximage3dmultisample = (PFNGLTEXIMAGE3DMULTISAMPLEPROC)get_proc("glTexImage3DMultisample");
	_gl_loader_gltexparameteriiv = (PFNGLTEXPARAMETERIIVPROC)get_proc("glTexParameterIiv");
	_gl_loader_gltexparameteriuiv = (PFNGLTEXPARAMETERIUIVPROC)get_proc("glTexParameterIuiv");
	_gl_loader_gltexparameterf = (PFNGLTEXPARAMETERFPROC)get_proc("glTexParameterf");
	_gl_loader_gltexparameterfv = (PFNGLTEXPARAMETERFVPROC)get_proc("glTexParameterfv");
	_gl_loader_gltexparameteri = (PFNGLTEXPARAMETERIPROC)get_proc("glTexParameteri");
	_gl_loader_gltexparameteriv = (PFNGLTEXPARAMETERIVPROC)get_proc("glTexParameteriv");
	_gl_loader_gltexstorage1d = (PFNGLTEXSTORAGE1DPROC)get_proc("glTexStorage1D");
	_gl_loader_gltexstorage2d = (PFNGLTEXSTORAGE2DPROC)get_proc("glTexStorage2D");
	_gl_loader_gltexstorage2dmultisample = (PFNGLTEXSTORAGE2DMULTISAMPLEPROC)get_proc("glTexStorage2DMultisample");
	_gl_loader_gltexstorage3d = (PFNGLTEXSTORAGE3DPROC)get_proc("glTexStorage3D");
	_gl_loader_gltexstorage3dmultisample = (PFNGLTEXSTORAGE3DMULTISAMPLEPROC)get_proc("glTexStorage3DMultisample");
	_gl_loader_gltexsubimage1d = (PFNGLTEXSUBIMAGE1DPROC)get_proc("glTexSubImage1D");
	_gl_loader_gltexsubimage2d = (PFNGLTEXSUBIMAGE2DPROC)get_proc("glTexSubImage2D");
	_gl_loader_gltexsubimage3d = (PFNGLTEXSUBIMAGE3DPROC)get_proc("glTexSubImage3D");
	_gl_loader_gltexturebarrier = (PFNGLTEXTUREBARRIERPROC)get_proc("glTextureBarrier");
	_gl_loader_gltexturebuffer = (PFNGLTEXTUREBUFFERPROC)get_proc("glTextureBuffer");
	_gl_loader_gltexturebufferrange = (PFNGLTEXTUREBUFFERRANGEPROC)get_proc("glTextureBufferRange");
	_gl_loader_gltextureparameteriiv = (PFNGLTEXTUREPARAMETERIIVPROC)get_proc("glTextureParameterIiv");
	_gl_loader_gltextureparameteriuiv = (PFNGLTEXTUREPARAMETERIUIVPROC)get_proc("glTextureParameterIuiv");
	_gl_loader_gltextureparameterf = (PFNGLTEXTUREPARAMETERFPROC)get_proc("glTextureParameterf");
	_gl_loader_gltextureparameterfv = (PFNGLTEXTUREPARAMETERFVPROC)get_proc("glTextureParameterfv");
	_gl_loader_gltextureparameteri = (PFNGLTEXTUREPARAMETERIPROC)get_proc("glTextureParameteri");
	_gl_loader_gltextureparameteriv = (PFNGLTEXTUREPARAMETERIVPROC)get_proc("glTextureParameteriv");
	_gl_loader_gltexturestorage1d = (PFNGLTEXTURESTORAGE1DPROC)get_proc("glTextureStorage1D");
	_gl_loader_gltexturestorage2d = (PFNGLTEXTURESTORAGE2DPROC)get_proc("glTextureStorage2D");
	_gl_loader_gltexturestorage2dmultisample = (PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC)get_proc("glTextureStorage2DMultisample");
	_gl_loader_gltexturestorage3d = (PFNGLTEXTURESTORAGE3DPROC)get_proc("glTextureStorage3D");
	_gl_loader_gltexturestorage3dmultisample = (PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC)get_proc("glTextureStorage3DMultisample");
	_gl_loader_gltexturesubimage1d = (PFNGLTEXTURESUBIMAGE1DPROC)get_proc("glTextureSubImage1D");
	_gl_loader_gltexturesubimage2d = (PFNGLTEXTURESUBIMAGE2DPROC)get_proc("glTextureSubImage2D");
	_gl_loader_gltexturesubimage3d = (PFNGLTEXTURESUBIMAGE3DPROC)get_proc("glTextureSubImage3D");
	_gl_loader_gltextureview = (PFNGLTEXTUREVIEWPROC)get_proc("glTextureView");
	_gl_loader_gltransformfeedbackbufferbase = (PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC)get_proc("glTransformFeedbackBufferBase");
	_gl_loader_gltransformfeedbackbufferrange = (PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC)get_proc("glTransformFeedbackBufferRange");
	_gl_loader_gltransformfeedbackvaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)get_proc("glTransformFeedbackVaryings");
	_gl_loader_gltranslated = (PFNGLTRANSLATEDPROC)get_proc("glTranslated");
	_gl_loader_gltranslatef = (PFNGLTRANSLATEFPROC)get_proc("glTranslatef");
	_gl_loader_gluniform1d = (PFNGLUNIFORM1DPROC)get_proc("glUniform1d");
	_gl_loader_gluniform1dv = (PFNGLUNIFORM1DVPROC)get_proc("glUniform1dv");
	_gl_loader_gluniform1f = (PFNGLUNIFORM1FPROC)get_proc("glUniform1f");
	_gl_loader_gluniform1fv = (PFNGLUNIFORM1FVPROC)get_proc("glUniform1fv");
	_gl_loader_gluniform1i = (PFNGLUNIFORM1IPROC)get_proc("glUniform1i");
	_gl_loader_gluniform1iv = (PFNGLUNIFORM1IVPROC)get_proc("glUniform1iv");
	_gl_loader_gluniform1ui = (PFNGLUNIFORM1UIPROC)get_proc("glUniform1ui");
	_gl_loader_gluniform1uiv = (PFNGLUNIFORM1UIVPROC)get_proc("glUniform1uiv");
	_gl_loader_gluniform2d = (PFNGLUNIFORM2DPROC)get_proc("glUniform2d");
	_gl_loader_gluniform2dv = (PFNGLUNIFORM2DVPROC)get_proc("glUniform2dv");
	_gl_loader_gluniform2f = (PFNGLUNIFORM2FPROC)get_proc("glUniform2f");
	_gl_loader_gluniform2fv = (PFNGLUNIFORM2FVPROC)get_proc("glUniform2fv");
	_gl_loader_gluniform2i = (PFNGLUNIFORM2IPROC)get_proc("glUniform2i");
	_gl_loader_gluniform2iv = (PFNGLUNIFORM2IVPROC)get_proc("glUniform2iv");
	_gl_loader_gluniform2ui = (PFNGLUNIFORM2UIPROC)get_proc("glUniform2ui");
	_gl_loader_gluniform2uiv = (PFNGLUNIFORM2UIVPROC)get_proc("glUniform2uiv");
	_gl_loader_gluniform3d = (PFNGLUNIFORM3DPROC)get_proc("glUniform3d");
	_gl_loader_gluniform3dv = (PFNGLUNIFORM3DVPROC)get_proc("glUniform3dv");
	_gl_loader_gluniform3f = (PFNGLUNIFORM3FPROC)get_proc("glUniform3f");
	_gl_loader_gluniform3fv = (PFNGLUNIFORM3FVPROC)get_proc("glUniform3fv");
	_gl_loader_gluniform3i = (PFNGLUNIFORM3IPROC)get_proc("glUniform3i");
	_gl_loader_gluniform3iv = (PFNGLUNIFORM3IVPROC)get_proc("glUniform3iv");
	_gl_loader_gluniform3ui = (PFNGLUNIFORM3UIPROC)get_proc("glUniform3ui");
	_gl_loader_gluniform3uiv = (PFNGLUNIFORM3UIVPROC)get_proc("glUniform3uiv");
	_gl_loader_gluniform4d = (PFNGLUNIFORM4DPROC)get_proc("glUniform4d");
	_gl_loader_gluniform4dv = (PFNGLUNIFORM4DVPROC)get_proc("glUniform4dv");
	_gl_loader_gluniform4f = (PFNGLUNIFORM4FPROC)get_proc("glUniform4f");
	_gl_loader_gluniform4fv = (PFNGLUNIFORM4FVPROC)get_proc("glUniform4fv");
	_gl_loader_gluniform4i = (PFNGLUNIFORM4IPROC)get_proc("glUniform4i");
	_gl_loader_gluniform4iv = (PFNGLUNIFORM4IVPROC)get_proc("glUniform4iv");
	_gl_loader_gluniform4ui = (PFNGLUNIFORM4UIPROC)get_proc("glUniform4ui");
	_gl_loader_gluniform4uiv = (PFNGLUNIFORM4UIVPROC)get_proc("glUniform4uiv");
	_gl_loader_gluniformblockbinding = (PFNGLUNIFORMBLOCKBINDINGPROC)get_proc("glUniformBlockBinding");
	_gl_loader_gluniformmatrix2dv = (PFNGLUNIFORMMATRIX2DVPROC)get_proc("glUniformMatrix2dv");
	_gl_loader_gluniformmatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)get_proc("glUniformMatrix2fv");
	_gl_loader_gluniformmatrix2x3dv = (PFNGLUNIFORMMATRIX2X3DVPROC)get_proc("glUniformMatrix2x3dv");
	_gl_loader_gluniformmatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)get_proc("glUniformMatrix2x3fv");
	_gl_loader_gluniformmatrix2x4dv = (PFNGLUNIFORMMATRIX2X4DVPROC)get_proc("glUniformMatrix2x4dv");
	_gl_loader_gluniformmatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)get_proc("glUniformMatrix2x4fv");
	_gl_loader_gluniformmatrix3dv = (PFNGLUNIFORMMATRIX3DVPROC)get_proc("glUniformMatrix3dv");
	_gl_loader_gluniformmatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)get_proc("glUniformMatrix3fv");
	_gl_loader_gluniformmatrix3x2dv = (PFNGLUNIFORMMATRIX3X2DVPROC)get_proc("glUniformMatrix3x2dv");
	_gl_loader_gluniformmatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)get_proc("glUniformMatrix3x2fv");
	_gl_loader_gluniformmatrix3x4dv = (PFNGLUNIFORMMATRIX3X4DVPROC)get_proc("glUniformMatrix3x4dv");
	_gl_loader_gluniformmatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)get_proc("glUniformMatrix3x4fv");
	_gl_loader_gluniformmatrix4dv = (PFNGLUNIFORMMATRIX4DVPROC)get_proc("glUniformMatrix4dv");
	_gl_loader_gluniformmatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)get_proc("glUniformMatrix4fv");
	_gl_loader_gluniformmatrix4x2dv = (PFNGLUNIFORMMATRIX4X2DVPROC)get_proc("glUniformMatrix4x2dv");
	_gl_loader_gluniformmatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)get_proc("glUniformMatrix4x2fv");
	_gl_loader_gluniformmatrix4x3dv = (PFNGLUNIFORMMATRIX4X3DVPROC)get_proc("glUniformMatrix4x3dv");
	_gl_loader_gluniformmatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)get_proc("glUniformMatrix4x3fv");
	_gl_loader_gluniformsubroutinesuiv = (PFNGLUNIFORMSUBROUTINESUIVPROC)get_proc("glUniformSubroutinesuiv");
	_gl_loader_glunmapbuffer = (PFNGLUNMAPBUFFERPROC)get_proc("glUnmapBuffer");
	_gl_loader_glunmapnamedbuffer = (PFNGLUNMAPNAMEDBUFFERPROC)get_proc("glUnmapNamedBuffer");
	_gl_loader_gluseprogram = (PFNGLUSEPROGRAMPROC)get_proc("glUseProgram");
	_gl_loader_gluseprogramstages = (PFNGLUSEPROGRAMSTAGESPROC)get_proc("glUseProgramStages");
	_gl_loader_glvalidateprogram = (PFNGLVALIDATEPROGRAMPROC)get_proc("glValidateProgram");
	_gl_loader_glvalidateprogrampipeline = (PFNGLVALIDATEPROGRAMPIPELINEPROC)get_proc("glValidateProgramPipeline");
	_gl_loader_glvertex2d = (PFNGLVERTEX2DPROC)get_proc("glVertex2d");
	_gl_loader_glvertex2dv = (PFNGLVERTEX2DVPROC)get_proc("glVertex2dv");
	_gl_loader_glvertex2f = (PFNGLVERTEX2FPROC)get_proc("glVertex2f");
	_gl_loader_glvertex2fv = (PFNGLVERTEX2FVPROC)get_proc("glVertex2fv");
	_gl_loader_glvertex2i = (PFNGLVERTEX2IPROC)get_proc("glVertex2i");
	_gl_loader_glvertex2iv = (PFNGLVERTEX2IVPROC)get_proc("glVertex2iv");
	_gl_loader_glvertex2s = (PFNGLVERTEX2SPROC)get_proc("glVertex2s");
	_gl_loader_glvertex2sv = (PFNGLVERTEX2SVPROC)get_proc("glVertex2sv");
	_gl_loader_glvertex3d = (PFNGLVERTEX3DPROC)get_proc("glVertex3d");
	_gl_loader_glvertex3dv = (PFNGLVERTEX3DVPROC)get_proc("glVertex3dv");
	_gl_loader_glvertex3f = (PFNGLVERTEX3FPROC)get_proc("glVertex3f");
	_gl_loader_glvertex3fv = (PFNGLVERTEX3FVPROC)get_proc("glVertex3fv");
	_gl_loader_glvertex3i = (PFNGLVERTEX3IPROC)get_proc("glVertex3i");
	_gl_loader_glvertex3iv = (PFNGLVERTEX3IVPROC)get_proc("glVertex3iv");
	_gl_loader_glvertex3s = (PFNGLVERTEX3SPROC)get_proc("glVertex3s");
	_gl_loader_glvertex3sv = (PFNGLVERTEX3SVPROC)get_proc("glVertex3sv");
	_gl_loader_glvertex4d = (PFNGLVERTEX4DPROC)get_proc("glVertex4d");
	_gl_loader_glvertex4dv = (PFNGLVERTEX4DVPROC)get_proc("glVertex4dv");
	_gl_loader_glvertex4f = (PFNGLVERTEX4FPROC)get_proc("glVertex4f");
	_gl_loader_glvertex4fv = (PFNGLVERTEX4FVPROC)get_proc("glVertex4fv");
	_gl_loader_glvertex4i = (PFNGLVERTEX4IPROC)get_proc("glVertex4i");
	_gl_loader_glvertex4iv = (PFNGLVERTEX4IVPROC)get_proc("glVertex4iv");
	_gl_loader_glvertex4s = (PFNGLVERTEX4SPROC)get_proc("glVertex4s");
	_gl_loader_glvertex4sv = (PFNGLVERTEX4SVPROC)get_proc("glVertex4sv");
	_gl_loader_glvertexarrayattribbinding = (PFNGLVERTEXARRAYATTRIBBINDINGPROC)get_proc("glVertexArrayAttribBinding");
	_gl_loader_glvertexarrayattribformat = (PFNGLVERTEXARRAYATTRIBFORMATPROC)get_proc("glVertexArrayAttribFormat");
	_gl_loader_glvertexarrayattribiformat = (PFNGLVERTEXARRAYATTRIBIFORMATPROC)get_proc("glVertexArrayAttribIFormat");
	_gl_loader_glvertexarrayattriblformat = (PFNGLVERTEXARRAYATTRIBLFORMATPROC)get_proc("glVertexArrayAttribLFormat");
	_gl_loader_glvertexarraybindingdivisor = (PFNGLVERTEXARRAYBINDINGDIVISORPROC)get_proc("glVertexArrayBindingDivisor");
	_gl_loader_glvertexarrayelementbuffer = (PFNGLVERTEXARRAYELEMENTBUFFERPROC)get_proc("glVertexArrayElementBuffer");
	_gl_loader_glvertexarrayvertexbuffer = (PFNGLVERTEXARRAYVERTEXBUFFERPROC)get_proc("glVertexArrayVertexBuffer");
	_gl_loader_glvertexarrayvertexbuffers = (PFNGLVERTEXARRAYVERTEXBUFFERSPROC)get_proc("glVertexArrayVertexBuffers");
	_gl_loader_glvertexattrib1d = (PFNGLVERTEXATTRIB1DPROC)get_proc("glVertexAttrib1d");
	_gl_loader_glvertexattrib1dv = (PFNGLVERTEXATTRIB1DVPROC)get_proc("glVertexAttrib1dv");
	_gl_loader_glvertexattrib1f = (PFNGLVERTEXATTRIB1FPROC)get_proc("glVertexAttrib1f");
	_gl_loader_glvertexattrib1fv = (PFNGLVERTEXATTRIB1FVPROC)get_proc("glVertexAttrib1fv");
	_gl_loader_glvertexattrib1s = (PFNGLVERTEXATTRIB1SPROC)get_proc("glVertexAttrib1s");
	_gl_loader_glvertexattrib1sv = (PFNGLVERTEXATTRIB1SVPROC)get_proc("glVertexAttrib1sv");
	_gl_loader_glvertexattrib2d = (PFNGLVERTEXATTRIB2DPROC)get_proc("glVertexAttrib2d");
	_gl_loader_glvertexattrib2dv = (PFNGLVERTEXATTRIB2DVPROC)get_proc("glVertexAttrib2dv");
	_gl_loader_glvertexattrib2f = (PFNGLVERTEXATTRIB2FPROC)get_proc("glVertexAttrib2f");
	_gl_loader_glvertexattrib2fv = (PFNGLVERTEXATTRIB2FVPROC)get_proc("glVertexAttrib2fv");
	_gl_loader_glvertexattrib2s = (PFNGLVERTEXATTRIB2SPROC)get_proc("glVertexAttrib2s");
	_gl_loader_glvertexattrib2sv = (PFNGLVERTEXATTRIB2SVPROC)get_proc("glVertexAttrib2sv");
	_gl_loader_glvertexattrib3d = (PFNGLVERTEXATTRIB3DPROC)get_proc("glVertexAttrib3d");
	_gl_loader_glvertexattrib3dv = (PFNGLVERTEXATTRIB3DVPROC)get_proc("glVertexAttrib3dv");
	_gl_loader_glvertexattrib3f = (PFNGLVERTEXATTRIB3FPROC)get_proc("glVertexAttrib3f");
	_gl_loader_glvertexattrib3fv = (PFNGLVERTEXATTRIB3FVPROC)get_proc("glVertexAttrib3fv");
	_gl_loader_glvertexattrib3s = (PFNGLVERTEXATTRIB3SPROC)get_proc("glVertexAttrib3s");
	_gl_loader_glvertexattrib3sv = (PFNGLVERTEXATTRIB3SVPROC)get_proc("glVertexAttrib3sv");
	_gl_loader_glvertexattrib4nbv = (PFNGLVERTEXATTRIB4NBVPROC)get_proc("glVertexAttrib4Nbv");
	_gl_loader_glvertexattrib4niv = (PFNGLVERTEXATTRIB4NIVPROC)get_proc("glVertexAttrib4Niv");
	_gl_loader_glvertexattrib4nsv = (PFNGLVERTEXATTRIB4NSVPROC)get_proc("glVertexAttrib4Nsv");
	_gl_loader_glvertexattrib4nub = (PFNGLVERTEXATTRIB4NUBPROC)get_proc("glVertexAttrib4Nub");
	_gl_loader_glvertexattrib4nubv = (PFNGLVERTEXATTRIB4NUBVPROC)get_proc("glVertexAttrib4Nubv");
	_gl_loader_glvertexattrib4nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)get_proc("glVertexAttrib4Nuiv");
	_gl_loader_glvertexattrib4nusv = (PFNGLVERTEXATTRIB4NUSVPROC)get_proc("glVertexAttrib4Nusv");
	_gl_loader_glvertexattrib4bv = (PFNGLVERTEXATTRIB4BVPROC)get_proc("glVertexAttrib4bv");
	_gl_loader_glvertexattrib4d = (PFNGLVERTEXATTRIB4DPROC)get_proc("glVertexAttrib4d");
	_gl_loader_glvertexattrib4dv = (PFNGLVERTEXATTRIB4DVPROC)get_proc("glVertexAttrib4dv");
	_gl_loader_glvertexattrib4f = (PFNGLVERTEXATTRIB4FPROC)get_proc("glVertexAttrib4f");
	_gl_loader_glvertexattrib4fv = (PFNGLVERTEXATTRIB4FVPROC)get_proc("glVertexAttrib4fv");
	_gl_loader_glvertexattrib4iv = (PFNGLVERTEXATTRIB4IVPROC)get_proc("glVertexAttrib4iv");
	_gl_loader_glvertexattrib4s = (PFNGLVERTEXATTRIB4SPROC)get_proc("glVertexAttrib4s");
	_gl_loader_glvertexattrib4sv = (PFNGLVERTEXATTRIB4SVPROC)get_proc("glVertexAttrib4sv");
	_gl_loader_glvertexattrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)get_proc("glVertexAttrib4ubv");
	_gl_loader_glvertexattrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)get_proc("glVertexAttrib4uiv");
	_gl_loader_glvertexattrib4usv = (PFNGLVERTEXATTRIB4USVPROC)get_proc("glVertexAttrib4usv");
	_gl_loader_glvertexattribbinding = (PFNGLVERTEXATTRIBBINDINGPROC)get_proc("glVertexAttribBinding");
	_gl_loader_glvertexattribdivisor = (PFNGLVERTEXATTRIBDIVISORPROC)get_proc("glVertexAttribDivisor");
	_gl_loader_glvertexattribformat = (PFNGLVERTEXATTRIBFORMATPROC)get_proc("glVertexAttribFormat");
	_gl_loader_glvertexattribi1i = (PFNGLVERTEXATTRIBI1IPROC)get_proc("glVertexAttribI1i");
	_gl_loader_glvertexattribi1iv = (PFNGLVERTEXATTRIBI1IVPROC)get_proc("glVertexAttribI1iv");
	_gl_loader_glvertexattribi1ui = (PFNGLVERTEXATTRIBI1UIPROC)get_proc("glVertexAttribI1ui");
	_gl_loader_glvertexattribi1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)get_proc("glVertexAttribI1uiv");
	_gl_loader_glvertexattribi2i = (PFNGLVERTEXATTRIBI2IPROC)get_proc("glVertexAttribI2i");
	_gl_loader_glvertexattribi2iv = (PFNGLVERTEXATTRIBI2IVPROC)get_proc("glVertexAttribI2iv");
	_gl_loader_glvertexattribi2ui = (PFNGLVERTEXATTRIBI2UIPROC)get_proc("glVertexAttribI2ui");
	_gl_loader_glvertexattribi2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)get_proc("glVertexAttribI2uiv");
	_gl_loader_glvertexattribi3i = (PFNGLVERTEXATTRIBI3IPROC)get_proc("glVertexAttribI3i");
	_gl_loader_glvertexattribi3iv = (PFNGLVERTEXATTRIBI3IVPROC)get_proc("glVertexAttribI3iv");
	_gl_loader_glvertexattribi3ui = (PFNGLVERTEXATTRIBI3UIPROC)get_proc("glVertexAttribI3ui");
	_gl_loader_glvertexattribi3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)get_proc("glVertexAttribI3uiv");
	_gl_loader_glvertexattribi4bv = (PFNGLVERTEXATTRIBI4BVPROC)get_proc("glVertexAttribI4bv");
	_gl_loader_glvertexattribi4i = (PFNGLVERTEXATTRIBI4IPROC)get_proc("glVertexAttribI4i");
	_gl_loader_glvertexattribi4iv = (PFNGLVERTEXATTRIBI4IVPROC)get_proc("glVertexAttribI4iv");
	_gl_loader_glvertexattribi4sv = (PFNGLVERTEXATTRIBI4SVPROC)get_proc("glVertexAttribI4sv");
	_gl_loader_glvertexattribi4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)get_proc("glVertexAttribI4ubv");
	_gl_loader_glvertexattribi4ui = (PFNGLVERTEXATTRIBI4UIPROC)get_proc("glVertexAttribI4ui");
	_gl_loader_glvertexattribi4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)get_proc("glVertexAttribI4uiv");
	_gl_loader_glvertexattribi4usv = (PFNGLVERTEXATTRIBI4USVPROC)get_proc("glVertexAttribI4usv");
	_gl_loader_glvertexattribiformat = (PFNGLVERTEXATTRIBIFORMATPROC)get_proc("glVertexAttribIFormat");
	_gl_loader_glvertexattribipointer = (PFNGLVERTEXATTRIBIPOINTERPROC)get_proc("glVertexAttribIPointer");
	_gl_loader_glvertexattribl1d = (PFNGLVERTEXATTRIBL1DPROC)get_proc("glVertexAttribL1d");
	_gl_loader_glvertexattribl1dv = (PFNGLVERTEXATTRIBL1DVPROC)get_proc("glVertexAttribL1dv");
	_gl_loader_glvertexattribl2d = (PFNGLVERTEXATTRIBL2DPROC)get_proc("glVertexAttribL2d");
	_gl_loader_glvertexattribl2dv = (PFNGLVERTEXATTRIBL2DVPROC)get_proc("glVertexAttribL2dv");
	_gl_loader_glvertexattribl3d = (PFNGLVERTEXATTRIBL3DPROC)get_proc("glVertexAttribL3d");
	_gl_loader_glvertexattribl3dv = (PFNGLVERTEXATTRIBL3DVPROC)get_proc("glVertexAttribL3dv");
	_gl_loader_glvertexattribl4d = (PFNGLVERTEXATTRIBL4DPROC)get_proc("glVertexAttribL4d");
	_gl_loader_glvertexattribl4dv = (PFNGLVERTEXATTRIBL4DVPROC)get_proc("glVertexAttribL4dv");
	_gl_loader_glvertexattriblformat = (PFNGLVERTEXATTRIBLFORMATPROC)get_proc("glVertexAttribLFormat");
	_gl_loader_glvertexattriblpointer = (PFNGLVERTEXATTRIBLPOINTERPROC)get_proc("glVertexAttribLPointer");
	_gl_loader_glvertexattribp1ui = (PFNGLVERTEXATTRIBP1UIPROC)get_proc("glVertexAttribP1ui");
	_gl_loader_glvertexattribp1uiv = (PFNGLVERTEXATTRIBP1UIVPROC)get_proc("glVertexAttribP1uiv");
	_gl_loader_glvertexattribp2ui = (PFNGLVERTEXATTRIBP2UIPROC)get_proc("glVertexAttribP2ui");
	_gl_loader_glvertexattribp2uiv = (PFNGLVERTEXATTRIBP2UIVPROC)get_proc("glVertexAttribP2uiv");
	_gl_loader_glvertexattribp3ui = (PFNGLVERTEXATTRIBP3UIPROC)get_proc("glVertexAttribP3ui");
	_gl_loader_glvertexattribp3uiv = (PFNGLVERTEXATTRIBP3UIVPROC)get_proc("glVertexAttribP3uiv");
	_gl_loader_glvertexattribp4ui = (PFNGLVERTEXATTRIBP4UIPROC)get_proc("glVertexAttribP4ui");
	_gl_loader_glvertexattribp4uiv = (PFNGLVERTEXATTRIBP4UIVPROC)get_proc("glVertexAttribP4uiv");
	_gl_loader_glvertexattribpointer = (PFNGLVERTEXATTRIBPOINTERPROC)get_proc("glVertexAttribPointer");
	_gl_loader_glvertexbindingdivisor = (PFNGLVERTEXBINDINGDIVISORPROC)get_proc("glVertexBindingDivisor");
	_gl_loader_glvertexp2ui = (PFNGLVERTEXP2UIPROC)get_proc("glVertexP2ui");
	_gl_loader_glvertexp2uiv = (PFNGLVERTEXP2UIVPROC)get_proc("glVertexP2uiv");
	_gl_loader_glvertexp3ui = (PFNGLVERTEXP3UIPROC)get_proc("glVertexP3ui");
	_gl_loader_glvertexp3uiv = (PFNGLVERTEXP3UIVPROC)get_proc("glVertexP3uiv");
	_gl_loader_glvertexp4ui = (PFNGLVERTEXP4UIPROC)get_proc("glVertexP4ui");
	_gl_loader_glvertexp4uiv = (PFNGLVERTEXP4UIVPROC)get_proc("glVertexP4uiv");
	_gl_loader_glvertexpointer = (PFNGLVERTEXPOINTERPROC)get_proc("glVertexPointer");
	_gl_loader_glviewport = (PFNGLVIEWPORTPROC)get_proc("glViewport");
	_gl_loader_glviewportarrayv = (PFNGLVIEWPORTARRAYVPROC)get_proc("glViewportArrayv");
	_gl_loader_glviewportindexedf = (PFNGLVIEWPORTINDEXEDFPROC)get_proc("glViewportIndexedf");
	_gl_loader_glviewportindexedfv = (PFNGLVIEWPORTINDEXEDFVPROC)get_proc("glViewportIndexedfv");
	_gl_loader_glwaitsync = (PFNGLWAITSYNCPROC)get_proc("glWaitSync");
	_gl_loader_glwindowpos2d = (PFNGLWINDOWPOS2DPROC)get_proc("glWindowPos2d");
	_gl_loader_glwindowpos2dv = (PFNGLWINDOWPOS2DVPROC)get_proc("glWindowPos2dv");
	_gl_loader_glwindowpos2f = (PFNGLWINDOWPOS2FPROC)get_proc("glWindowPos2f");
	_gl_loader_glwindowpos2fv = (PFNGLWINDOWPOS2FVPROC)get_proc("glWindowPos2fv");
	_gl_loader_glwindowpos2i = (PFNGLWINDOWPOS2IPROC)get_proc("glWindowPos2i");
	_gl_loader_glwindowpos2iv = (PFNGLWINDOWPOS2IVPROC)get_proc("glWindowPos2iv");
	_gl_loader_glwindowpos2s = (PFNGLWINDOWPOS2SPROC)get_proc("glWindowPos2s");
	_gl_loader_glwindowpos2sv = (PFNGLWINDOWPOS2SVPROC)get_proc("glWindowPos2sv");
	_gl_loader_glwindowpos3d = (PFNGLWINDOWPOS3DPROC)get_proc("glWindowPos3d");
	_gl_loader_glwindowpos3dv = (PFNGLWINDOWPOS3DVPROC)get_proc("glWindowPos3dv");
	_gl_loader_glwindowpos3f = (PFNGLWINDOWPOS3FPROC)get_proc("glWindowPos3f");
	_gl_loader_glwindowpos3fv = (PFNGLWINDOWPOS3FVPROC)get_proc("glWindowPos3fv");
	_gl_loader_glwindowpos3i = (PFNGLWINDOWPOS3IPROC)get_proc("glWindowPos3i");
	_gl_loader_glwindowpos3iv = (PFNGLWINDOWPOS3IVPROC)get_proc("glWindowPos3iv");
	_gl_loader_glwindowpos3s = (PFNGLWINDOWPOS3SPROC)get_proc("glWindowPos3s");
	_gl_loader_glwindowpos3sv = (PFNGLWINDOWPOS3SVPROC)get_proc("glWindowPos3sv");
	close_gl();
}
