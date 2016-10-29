/*
	QMPlay2 is a video and audio player.
	Copyright (C) 2010-2016  Błażej Szczygieł

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef VIDEOWRITER_HPP
#define VIDEOWRITER_HPP

#include <PixelFormats.hpp>
#include <Writer.hpp>

class HWAccellInterface;
class QMPlay2_OSD;
class VideoFrame;
class ImgScaler;

class VideoWriter : public Writer
{
public:
	VideoWriter();

	virtual QMPlay2PixelFormats supportedPixelFormats() const;

	qint64 write(const QByteArray &);

	virtual void writeVideo(const VideoFrame &videoFrame) = 0;
	virtual void writeOSD(const QList<const QMPlay2_OSD *> &osd) = 0;

	virtual void setHWAccellInterface(HWAccellInterface *hwAccellInterface);
	inline HWAccellInterface *getHWAccellInterface() const
	{
		return m_hwAccellInterface;
	}

	virtual bool hwAccellGetImg(const VideoFrame &videoFrame, void *dest, ImgScaler *nv12ToRGB32) const;

	virtual bool open() = 0;

protected:
	HWAccellInterface *m_hwAccellInterface;
};

#endif //VIDEOWRITER_HPP
