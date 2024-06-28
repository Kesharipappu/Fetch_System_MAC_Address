#include "mainwindow.h"
#include <QApplication>
#include <QCoreApplication>
#include <QNetworkInterface>
#include <QNetworkAddressEntry>
#include <QDebug>
#include <QInputDialog> // Include QInputDialog for GUI-based input

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Get all network interfaces
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();

    qDebug() << "Connected Networks with this System are:";
    qDebug() << endl;
//#if 0
    // Display fetched network interfaces and MAC addresses
    for (const QNetworkInterface &interface : interfaces)
    {
        // Check if the interface is up and running
        if (interface.flags() & QNetworkInterface::IsUp && interface.flags() & QNetworkInterface::IsRunning)
        {
            // Get the MAC address
            QString macAddress = interface.hardwareAddress();
            if (!macAddress.isEmpty())
            {
                qDebug() << "Interface Name:" << interface.humanReadableName();
                qDebug() << "MAC Address:" << macAddress;

                // Get all IP addresses associated with this interface
                QList<QNetworkAddressEntry> entries = interface.addressEntries();
                for (const QNetworkAddressEntry &entry : entries)
                {
                    QHostAddress ipAddress = entry.ip();
                    if (!ipAddress.isNull())
                    {
                        qDebug() << "IP Address:" << ipAddress.toString();
                    }
                }
                qDebug() << endl;
            }
        }
    }
//#endif

    // Prompt user to enter MAC address using QInputDialog
    bool ok;
    QString userInput = QInputDialog::getText(0, "Input Dialog", "Enter MAC Address to check:", QLineEdit::Normal, "", &ok);

    if (ok && !userInput.isEmpty())
    {
        qDebug() << "User entered MAC Address:" << userInput;

        bool found = false;
        // Iterate again to check user-input MAC address
        for (const QNetworkInterface &interface : interfaces)
        {
            if (interface.flags() & QNetworkInterface::IsUp && interface.flags() & QNetworkInterface::IsRunning)
            {
                QString macAddress = interface.hardwareAddress();
                if (macAddress == userInput)
                {
                    found = true;
                    break;
                }
            }
        }
        // Display result based on comparison
        qDebug() << "Result:" << (found ? "True" : "False");
    }
    else
    {
        qDebug() << "No input provided.";
    }
    return a.exec();
}
