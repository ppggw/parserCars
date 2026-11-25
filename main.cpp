#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <QUdpSocket>


#include <thread>
#include <iostream>
#include <bit>
#include <array>


int main(int argc, char *argv[])
{
    QFile* file_for_write_hex_data = new QFile("/home/shine/QtProjects/readShineLog/25_11_2026__12_21/25_11_2026__14_12.txt");
    bool log_file_is_open = file_for_write_hex_data->open(QIODevice::ReadOnly);
    if(!log_file_is_open){
        qDebug() << "oopss";
    }

    QTextStream* stream_for_write_log = new QTextStream();
    stream_for_write_log->setDevice(file_for_write_hex_data);

    QUdpSocket* udpSocket = new QUdpSocket();
    udpSocket->bind(QHostAddress("127.0.0.99"), 6767);

    while (!stream_for_write_log->atEnd()) {
        QString line = stream_for_write_log->readLine();
        QByteArray byteArray = QByteArray::fromHex(line.toUtf8());

        qDebug() << byteArray.toHex();

        udpSocket->writeDatagram(byteArray, QHostAddress("127.0.0.101"), 56123);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    file_for_write_hex_data->close();

    // std::array<uint8_t, 8> bytes1 = {0xf6, 0x1e, 0x54, 0xb1, 0xda, 0xd5, 0x0b, 0x40};
    // std::array<uint8_t, 8> bytes2 = {0xbf, 0xcc, 0xde, 0xeb, 0x94, 0xd9, 0x0b, 0x40};
    // std::array<uint8_t, 8> bytes3 = {0x10, 0x6e, 0x2e, 0xeb, 0x94, 0xdd, 0x0b, 0x40};
    // std::array<uint8_t, 8> bytes4 = {0xeb, 0xc2, 0x39, 0x19, 0x4a, 0xe1, 0x0b, 0x40};
    // std::array<uint8_t, 8> bytes5 = {0xa2, 0x0d, 0xcc, 0x6f, 0xf8, 0xe4, 0x0b, 0x40};


    // double value1 = std::bit_cast<double>(bytes1);
    // double value2 = std::bit_cast<double>(bytes2);
    // double value3 = std::bit_cast<double>(bytes3);
    // double value4 = std::bit_cast<double>(bytes4);
    // double value5 = std::bit_cast<double>(bytes5);

    // std::cout << "Результат: " << value1 * (180./3.15) << std::endl;
    // std::cout << "Результат: " << value2 * (180./3.15) << std::endl;
    // std::cout << "Результат: " << value3 * (180./3.15) << std::endl;
    // std::cout << "Результат: " << value4 * (180./3.15) << std::endl;
    // std::cout << "Результат: " << value5 * (180./3.15) << std::endl;
    // return 0;

    // std::array<uint8_t, 8> bytes1 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x40};
    // std::array<uint8_t, 8> bytes2 = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x40};


    // double value1 = std::bit_cast<double>(bytes1);
    // double value2 = std::bit_cast<double>(bytes2);


    // std::cout << "Результат: " << value1 * (180./3.15) << std::endl;
    // std::cout << "Результат: " << value2 * (180./3.15) << std::endl;
    // return 0;
}
