##################################################
# マイクロマウス用シミュレータ
#                           2022/07/06 K. Richardo
###################################################

#################################
# ライブラリのインポート
#################################
import sys
import os
import math
import numpy as np
import csv

import matplotlib
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasAgg as FigureCanvas
from matplotlib.figure import Figure

from PyQt5 import QtWidgets, QtCore, QtGui, uic
from PyQt5.QtCore import QThread, QObject, pyqtSignal

import operator
import serial
import serial.tools.list_ports
from datetime import datetime

#################################
# グローバル変数定義
#################################
uiMainWindow, _= uic.loadUiType('simulator.ui')

#################################
# Windowのクラス
#################################
class mainWindow(QtWidgets.QMainWindow, uiMainWindow):
    # -------------------------------
    # 初期化
    def __init__(self):
        # Windowの表示
        QtWidgets.QMainWindow.__init__(self)
        uiMainWindow.__init__(self)
        self.setupUi(self)

        # Baudrate 115200にデフォルト表示
        # 0: 9600, 1: 19200, 2: 38400, 3: 57600, 4: 115200
        self.CBoxBaudrate.setCurrentIndex(4)

        # 使用可能COMポートを表示
        self.get_available_com_ports()

        # ボタンを関数に接続
        self.BPortRefresh.clicked.connect(self.BPortRefresh_Clicked)
        self.BConnect.clicked.connect(self.BConnect_Clicked)

    # -------------------------------
    # 使用可能COMポート取得
    def get_available_com_ports(self):
        self.CBoxPort.clear()

        self.available_ports_all = list( serial.tools.list_ports.comports() )
        self.available_ports = [port for port in self.available_ports_all if port[2] != 'n/a']
        self.available_ports.sort(key=operator.itemgetter(1))

        for port, desc, _ in self.available_ports:
            self.CBoxPort.addItem(port)

    # -------------------------------
    # COMポートを再読み込み
    def BPortRefresh_Clicked(self):
        self.get_available_com_ports()

    # -------------------------------
    # COMポートに接続
    def BConnect_Clicked(self):
        global uart
        (self.selected_port, _, _) = self.available_ports[ self.CBoxPort.currentIndex() ]
        self.selected_baudrate = self.CBoxBaudrate.currentText()

        # Opening COM Port
        try:
            print("Opening %s" % self.selected_port)
            print("Baud rate %s" % self.selected_baudrate)
            uart = serial.Serial(
                self.selected_port,
                self.selected_baudrate,
                timeout = 1,
                bytesize = serial.EIGHTBITS,
                parity = serial.PARITY_NONE,
                stopbits = serial.STOPBITS_ONE
            )
            self.LConnStatus.setText("Connected")

        except serial.SerialException:
            print("[!] Unable to open %s." % self.selected_port)
            self.LConnStatus.setText("Error")
            exit(-1)
        
        uart.write(b'"1"')
        while True:
            c = uart.read()
            print(c)
            if c == 'end':
                break
        
        uart.close()

        # CSV出力
        # timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        # output_dir = "_output/" + timestamp
        # output_csv_dir = output_dir + "data.csv"
        # with open( output_csv_dir, 'w', encoding='UTF8', newline='' ) as f:
        #     writer = csv.writer(f)
            
        
        

#################################
# スレッドのクラス
#################################
    
#################################
# main関数
#################################
if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    window = mainWindow()
    window.show()
    app.exec()