/*
 * Copyright (c) 2010-2012 OTClient <https://github.com/edubart/otclient>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef TEXTURE_H
#define TEXTURE_H

#include "declarations.h"

class Texture : public std::enable_shared_from_this<Texture>
{
public:
    Texture();
    Texture(const ImagePtr& image);
    Texture(int width, int height, int channels = 4, uchar* pixels = NULL);
    virtual ~Texture();

    void copyFromScreen(const Rect& screenRect);

    void bind();

    /// Tries to generate mipmaps via hardware, otherwise fallback to software implementation
    void generateMipmaps();
    /// Generate mipmaps via hardware if supported
    bool generateHardwareMipmaps();
    /// Generate mipmaps via software, which has a special algorithm for combining alpha pixels
    void generateSoftwareMipmaps(std::vector<uint8> inPixels);

    /// Activate texture anti-aliasing giving a better look when they are resized
    void setSmooth(bool smooth);
    void setUpsideDown(bool upsideDown);

    GLuint getId()  { return m_textureId; }

    int getWidth() { return m_size.width(); }
    int getHeight() { return m_size.height(); }
    const Size& getSize() { return m_size; }
    const Matrix3& getTransformMatrix() { return m_transformMatrix; }

    bool isEmpty() { return m_textureId == 0; }
    bool hasMipmaps() { return m_hasMipmaps; }

protected:
    void setupFilters();
    void setupTranformMatrix();
    GLuint internalLoadGLTexture(uchar* pixels, int channels, int w, int h);

    GLuint m_textureId;
    Size m_size;
    Size m_glSize;
    Matrix3 m_transformMatrix;
    Boolean<false> m_hasMipmaps;
    Boolean<false> m_smooth;
    Boolean<false> m_upsideDown;
};

#endif
