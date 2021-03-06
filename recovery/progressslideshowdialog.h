#ifndef PROGRESSSLIDESHOWDIALOG_H
#define PROGRESSSLIDESHOWDIALOG_H

/* Progress dialog with slideshow
 *
 * Initial author: Floris Bos
 * Maintained by Raspberry Pi
 *
 * See LICENSE.txt for license details
 *
 */

#include <QProgressDialog>
#include <QTimer>
#include <QTime>

namespace Ui {
class ProgressSlideshowDialog;
}

class ProgressSlideshowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressSlideshowDialog(const QStringList &slidesDirectories, const QString &statusMsg = "", int changeInterval = 20, const QString &drive = "/dev/mmcblk0", QWidget *parent = 0, bool readmode=false);
    ~ProgressSlideshowDialog();
    void enableIOaccounting();
    void disableIOaccounting();

public slots:
    void setLabelText(const QString &text);
    void setMBWrittenText(const QString &text);
    void setMaximum(qint64 bytes);
    void nextSlide();
    void updateIOstats();
    void pauseIOaccounting();
    void resumeIOaccounting();
    void captureIOaccounting(uint *paused=NULL);
    void restoreIOaccounting(uint paused=0);
    void updateProgress(qint64 value);
    void changeDrive(const QString &drive);

protected:
    QString _drive;
    QStringList _slides;
    int _pos, _changeInterval;
    uint _sectorsStart, _maxSectors, _pausedAt;
    QTimer _timer, _iotimer;
    QTime _t1;
    bool _readmode;

    uint sectorsAccessed();


private:
    Ui::ProgressSlideshowDialog *ui;
};

#endif // PROGRESSSLIDESHOWDIALOG_H
