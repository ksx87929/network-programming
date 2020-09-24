using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;
using System.Net;
using System.Net.Sockets;


namespace _007
{
    
    public partial class Form1 : Form
    {
        int STATE = 1;
        TcpClient client2;
        NetworkStream stream,stream2;
        int count;
        int score=0;
        int partsc = 60;
        int m, t;
        int place = 0;
        int time = 0;
        Button first = null;
        Button second = null;
        Button[] btn = new Button[36];
        Random rnd = new Random();
        int[] Num = new int[36];
        int[] RndArr = new int[36];
        List<string> arr = new List<string>();
        string tempdata="",tempplace="",sendsymbol="";
        int UI_stas = 1; //判斷UI狀態  
        bool state = true ,init = true;
        int location = -1, templocat = 0;
        Byte[] databtn;

        IPEndPoint remoteIP;
        Socket Server;
        byte[] pushdata = new byte[1024]; //定義要送出的封包大小

        EndPoint IP;
        IPEndPoint IPEnd;
        Socket Client;
        byte[] getdata = new byte[1024]; //要接收的封包大小
        string input;
        int recv;
        enum E
        {
            recived = 1, strat = 2 , display = 3, disconnected = 4,
        }
        //列舉判斷代碼，方便辨識  
        List<string> _Ls = new List<string>();
        private void getData()
        {

            TcpListener server = null;
            try
            {
                // 設置 TcpListener port 5678. 
                Int32 port = 5678;
                IPAddress localAddr = IPAddress.Parse("127.0.0.1");
                server = new TcpListener(localAddr, port);
                //建立新的TcpListener  
                server.Start();//開始監聽client的請求  
                Byte[] bytes = new Byte[256]; //建立buffer來讀取資料  
                String data = "";
                // 進入監聽迴圈  
                while (true)
                {
                    //傳入一個變數訊息給ReportProgress借以改變UI  
                    //，直接在執行緒修改UI是不被允許  
                    TcpClient client = server.AcceptTcpClient();
                    //接收client端的請求  
                    UI_stas = Convert.ToInt32(E.strat);
                    backgroundWorker1.ReportProgress(UI_stas);
                    
                    data = null;
                    NetworkStream stream = client.GetStream();
                    //取得client傳過來的資料  
                    int i;
                    // 開始接收 client 的資料
                    while ((i = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        data = System.Text.Encoding.Unicode.GetString(bytes, 0, i);
                        if(init==true)
                        { 
                            UI_stas = Convert.ToInt32(E.display);
                            if (data != "disconnect")
                            {
                                _Ls.Add(data);//接收到的資存入List  
                            }
                            backgroundWorker1.ReportProgress(UI_stas, data);
                            init = false;

                        }
                        else
                        {
                            _Ls.Clear();
                            UI_stas = Convert.ToInt32(E.recived);
                            _Ls.Add(data);
                            backgroundWorker1.ReportProgress(UI_stas, data);
                        }
                    }
                    
                    UI_stas = Convert.ToInt32(E.disconnected);
                    backgroundWorker1.ReportProgress(UI_stas);
                    client.Close();
                }
            }
            catch (SocketException e)
            {
                MessageBox.Show("SocketException:{0}" + e); //偵錯
            }
            finally //釋放區塊  
            {
                server.Stop();//停止監聽clients  
            }

        }
        private void Form1_Load(object sender, EventArgs e)
        {
            backgroundWorker1.RunWorkerAsync();
        }
        
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            getData();
        }
        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            MessageBox.Show("OK");
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e) //此部分為看接收值改變UI  
        {
            
            if (e.ProgressPercentage == (int)E.recived)
            {

                foreach (string data in _Ls)
                {
                    
                    tempdata = "";
                    tempplace = "";
                    
                    //MessageBox.Show(data.ToString());
                    for (int i=0;i<data.Length; i++)
                    {
                        if (i == 0)
                            tempdata +=data[i];
                        else
                            tempplace +=data[i];
                    }
                    if (location == -1)
                    {
                        location = Convert.ToInt32(tempplace);
                        templocat = location;
                        btn[location].ForeColor = Color.Black;
                        btn[location].BackColor = Color.Wheat;
                    }
                    else
                    {
                        location = Convert.ToInt32(tempplace);
                        btn[location].ForeColor = Color.Black;
                        btn[location].BackColor = Color.Wheat;
                        
                        if (btn[location].Text != btn[templocat].Text )
                        {
                            btn[location].ForeColor = Color.Moccasin;
                            btn[location].BackColor = Color.Moccasin;
                            btn[templocat].ForeColor = Color.Moccasin;
                            btn[templocat].BackColor = Color.Moccasin;
                            state = false;
                            location = -1;
                        }
                        else
                            location = -1;
                        recv = Client.ReceiveFrom(getdata, ref IP); //把接收的封包放進getdata且傳回大小存入recv
                        input = Encoding.UTF8.GetString(getdata, 0, recv); //把接收的byte資料轉回string型態
                        //MessageBox.Show(input);
                        if (input != "")
                            label3.Text = "對手的分數 : " + input;
                        Console.WriteLine("received: {0} from: {1}", input, IP.ToString());

                    }
                }
            }
            else if (e.ProgressPercentage == (int)E.strat)
            {
                if (e.ProgressPercentage != (int)E.disconnected)
                {
                    //label2.Text = "Connected!";
                }
            }
            else if (e.ProgressPercentage == (int)E.display && e.UserState.ToString() != "disconnect")
            {
               
                foreach (string data in _Ls)
                {
                    tempdata += data;
                }
            }
            if (e.ProgressPercentage == (int)E.disconnected)
            {
                //label2.Text = "disonnected!";
            }
        }


        public Form1()
        {
            InitializeComponent();
            btn = new Button[36] { button1, button2, button3, button4, button5, button6,
                button7, button8, button9, button10, button11, button12, button13, button14,
                button15, button16, button17, button18, button19, button20, button21, button22,
                button23, button24, button25, button26, button27, button28, button29, button30,
                button31, button32, button33, button34, button35, button36 };

        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        private void button37_Click(object sender, EventArgs e)
        {
            int num;
            m = 0;
            t = 0;
            time = 0;
            count = 0;
            score = 0;
            timer2.Start();
            //MessageBox.Show(tempdata);
            for (int i = 0; i < 36; i++)
            {
                //btn[i].Click += new EventHandler(this.buttons_Click);//1062981
                btn[i].Text += tempdata[i];
                btn[i].ForeColor = System.Drawing.Color.Moccasin;
            }
            button37.Enabled = false;

            Int32 port2 = 7777;
            client2 = new TcpClient("127.0.0.2", port2);

            databtn = System.Text.Encoding.Unicode.GetBytes("check");
            stream2 = client2.GetStream(); // 取得clientstream  
            stream2.Write(databtn, 0, databtn.Length);

            for(int i=0;i<36;i++)
                btn[i].Click += new EventHandler(this.buttons_Click);
            remoteIP = new IPEndPoint(IPAddress.Parse("127.0.0.3"), 7778); //可自行定義廣播區域跟Port
            Server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp); //定義發送的格式及有效區域
            Server.EnableBroadcast = true;
            Server.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Broadcast, true);

            Client = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
            button37.Enabled = false;
            IPEnd = new IPEndPoint(IPAddress.Parse("127.0.0.4"), 7779);
            Client.Bind(IPEnd);
            IP = (EndPoint)IPEnd;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (partsc > 0)
                partsc -= 5;
            else
                partsc = 0;
            timer1.Stop();
            Thread.Sleep(300);
            first.ForeColor = Color.Moccasin;
            first.BackColor = Color.Moccasin;
            second.ForeColor = Color.Moccasin;
            second.BackColor = Color.Moccasin;
            first = null;
            second = null;

        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            if (t >= 60)
            {
                m++;
                t =0;
            }
           
            //label2.Text = " 時間：" + m + " 分 " + t + " 秒 ";
            timer2.Interval = 1000;
            t++;
        }

        


        private void buttons_Click(object sender,EventArgs e)
        {
            string strbtn = "";

            Button button = (Button)sender;
            strbtn = sender.ToString();
           

            sendsymbol = "";
            sendsymbol += strbtn[strbtn.Length - 1];
            if (state == false)
            {
                if (button.ForeColor == Color.Red)
                    return;
                if (first == null)
                {
                    first = button;
                    first.ForeColor = Color.Red;
                    first.BackColor = Color.Wheat;
                    for (int i = 0; i < 36; i++)
                    {
                        if (first.ForeColor == btn[i].ForeColor && btn[i] == first)
                        {
                            place = i;
                            sendsymbol += i.ToString();
                        }
                    }
                    //MessageBox.Show(sendsymbol);
                    databtn = System.Text.Encoding.Unicode.GetBytes(sendsymbol);
                    stream2 = client2.GetStream(); // 取得clientstream  
                    stream2.Write(databtn, 0, databtn.Length);
                    return;

                }
                else
                {
                    second = button;
                    second.ForeColor = Color.Red;
                    second.BackColor = Color.Wheat;
                    for (int i = 0; i < 36; i++)
                    {
                        if (second.ForeColor == btn[i].ForeColor && btn[i] == second && i != place)
                        {

                            sendsymbol += i.ToString();
                            place = 0;
                        }
                    }

                    databtn = System.Text.Encoding.Unicode.GetBytes(sendsymbol);
                    stream2 = client2.GetStream(); // 取得clientstream  
                    stream2.Write(databtn, 0, databtn.Length);
                }

                if (first.Text != second.Text)
                {
                    timer1.Start();
                    state = true;
                }
                else
                {
                    count = 0;
                    for (int i = 0; i < 36; i++)
                    {
                        if (btn[i].ForeColor == Color.Black)
                            count++;

                        if (count == 35)
                        {
                            score += m * 200;
                            score += t * 3;
                            timer2.Stop();
                            label1.Text = "你的分數 ： " + score;
                            time = m * 60 + t;
                            MessageBox.Show(" 完成遊戲!! \n " + "共得到 ：" + score + " 分 \n 完成時間 ：" + time + "秒");
                            this.Close();
                        }
                    }
                    if (partsc == 60)
                    {
                        score += 30 * (36 - count);
                    }
                    else if (partsc > 40)
                    {
                        score += partsc + (36 - count);
                    }
                    else if (partsc > 20)
                    {
                        score += partsc;
                    }
                    else
                    {
                        score += 20;
                    }
                    partsc = 60;
                    label1.Text = "你的分數 ： " + score;
                    first = null;
                    second = null;

                }
            }
            string tstr;
            tstr = score.ToString();
            //MessageBox.Show(tstr);
            pushdata = Encoding.UTF8.GetBytes(tstr); //把要送出的資料轉成byte型態
            Server.SendTo(pushdata, remoteIP); //送出的資料跟目的

        }


    }
}







