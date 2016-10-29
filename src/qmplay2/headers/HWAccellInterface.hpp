#ifndef HWACCELLINTERFACE_HPP
#define HWACCELLINTERFACE_HPP

#include <QString>

class VideoFrame;
class ImgScaler;

class HWAccellInterface
{
public:
	enum Field
	{
		FullFrame,
		TopField,
		BottomField
	};

	virtual ~HWAccellInterface()
	{}

	virtual QString name() const = 0;

	virtual bool lock() = 0;
	virtual bool unlock() = 0;

	virtual bool init(quint32 *textures) = 0;
	virtual void clear() = 0;

	virtual bool copyFrame(const VideoFrame &videoFrame, Field field) = 0;

	virtual bool getImage(const VideoFrame &videoFrame, void *dest, ImgScaler *yv12ToRGB32 = NULL) = 0;
};

#endif // HWACCELLINTERFACE_HPP
