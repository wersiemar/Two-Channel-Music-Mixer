#ifndef MIXPANEL_H
#define MIXPANEL_H

#include <QObject>

#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioDecoder>

#include "math.h"

class MixPanel : public QObject
{
    Q_OBJECT

private:
    struct memEQ {
        double xmem1, xmem2, ymem1, ymem2;
        double b0, b1, b2, a0, a1, a2;
    };

public:
    explicit MixPanel(QObject *parent = nullptr);
    ~MixPanel();

    double processEQ(double sample, memEQ &eq);
    double processLow(double sample);
    double processMedium(double sample);
    double processHigh(double sample);

    void process(double *buffer, int nFrames);

    void shelfFilter(double F0, double g, QString type, memEQ &eq);

private:
    QAudioDecoder *decoder;

    QByteArray *channel1;
    QByteArray *channel2;

    memEQ lowMemEq;
    memEQ medMemEq;
    memEQ medMemEq2;
    memEQ highMemEq;

    bool audioReady;
    bool isWhiteNoise;
    bool isPlayed;

    qint64 duration;
    qint64 actPos;

signals:
    void timeChange(QString time);

public slots:
    void playPause();

    void loadAudio(QString filename);
    void readBuffer();
    void finishDecoding();

    void enableWhiteNoise();
    void disableWhiteNoise();

    void lowEQ(int value);
    void medEQ(int value);
    void highEQ(int value);
};

#endif // MIXPANEL_H