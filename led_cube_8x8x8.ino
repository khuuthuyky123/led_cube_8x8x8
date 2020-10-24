//byte DS=A1;
//byte STCP=A2;
//byte SHCP=A3;
int Tangz[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
 Serial.begin(9600);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
  for (int x = 0; x < 8; x++) {
    pinMode(Tangz[x], OUTPUT);
  }
}

void loop() {
  
    mua(100, 60);
    plane('X', 4);
    plane('Y', 4);
    plane('Z', 4);
    plane2('X', 4);
    plane2('Y', 4);
    plane2('Z', 4);
}

void mua(int solanmua, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    for (byte s = 0; s < solanmua; s++)
    {
        byte n = random(1, 5); // chọn ngẫu nhiên số hạt mưa rơi
        for (byte h = 0; h < n; h++)
        {
            byte x = random(0, 8); // chọn ngẫu nhiên một toạ độ hạt mưa
            byte y = random(0, 8);
            mangba[x][y][7] = 1; // Cho cái hạt mưa đó =1 để cái đèn đó sáng lên
        }
        hienthi(mangba, Solan); // hiển thị
        for (byte z = 0; z < 7; z++)
        { // dời các tầng z xuống một tầng
            for (byte x = 0; x < 8; x++)
            { // nhưng phải giữ nguyên toạ độ theo x, y để mưa rơi thẳng
                for (byte y = 0; y < 8; y++)
                {
                    mangba[x][y][z] = mangba[x][y][z + 1];
                }
            }
        }
        for (byte x = 0; x < 8; x++)
        {
            for (byte y = 0; y < 8; y++)
            {
                mangba[x][y][7] = 0; // trả tầng z=7 về 0
            }
        }
    }
}

void plane(char truc, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    for (byte i = 0; i < 8; i++)
    {
        for (byte z = 0; z < 8; z++)
        {
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    mangba[x][y][z] = 0;
                    if (truc == 'X')
                    {
                        mangba[i][y][z] = 1;
                    }
                    if (truc == 'Y')
                    {
                        mangba[x][i][z] = 1;
                    }
                    if (truc == 'Z')
                    {
                        mangba[x][y][i] = 1;
                    }
                }
            }
        }
        hienthi(mangba, Solan);
    }
    for (int i = 7; i >= 0; i--)
    {
        for (byte z = 0; z < 8; z++)
        {
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    mangba[7 - x][7 - y][7 - z] = 0;
                    if (truc == 'X')
                    {
                        mangba[i][7 - y][7 - z] = 1;
                    }
                    if (truc == 'Y')
                    {
                        mangba[7 - x][i][7 - z] = 1;
                    }
                    if (truc == 'Z')
                    {
                        mangba[7 - x][7 - y][i] = 1;
                    }
                }
            }
        }
        hienthi(mangba, Solan);
    }
}

void plane2(char truc, byte Solan)
{
    byte mangba[8][8][8] = { 0 };
    byte manghai[8][8] = { 0 }; //Đây là mảng dùng để đánh dấu là đèn nào đã bị bỏ lại
    for (byte x = 0; x < 8; x++)
    { // Tạo ra một mảng sáng trước khi dời đi
        for (byte y = 0; y < 8; y++)
        {
            if (truc == 'X')
            {
                mangba[0][x][y] = 1;
            }
            else if (truc == 'Y')
            {
                mangba[x][0][y] = 1;
            }
            else
            {
                mangba[x][y][0] = 1;
            }
        }
    }
    hienthi(mangba, Solan * 2);
    for (byte i = 1; i < 8; i++)
    { // Do đã tạo 1 mảng sáng trước rồi nên chỉ cần dời mảng này đi trong 7 lần
        byte u = 0;
        while (u < 8)
        { // tại mỗi lần rời đi, ta bỏ lại 8 điểm ngẫu nhiên
            byte x = random(8);
            byte y = random(8);
            if (manghai[x][y] == 0)
            {
                manghai[x][y] = 1;
                u = u + 1;
                hienthi(mangba, 1); // do sư ngẫu nhiên có thể bị trùng, nên ta thêm lệnh này để
                                    // hình ảnh được liên tục
            }
        }
        for (byte x = 0; x < 8; x++)
        { // Bắt đầu việc dời trục
            for (byte y = 0; y < 8; y++)
            {
                if (manghai[x][y] == 0)
                {
                    if (truc == 'X')
                    {
                        mangba[i][x][y] = 1;
                        mangba[i - 1][x][y] = 0;
                    }
                    else if (truc == 'Y')
                    {
                        mangba[x][i][y] = 1;
                        mangba[x][i - 1][y] = 0;
                    }
                    else if (truc == 'Z')
                    {
                        mangba[x][y][i] = 1;
                        mangba[x][y][i - 1] = 0;
                    }
                }
            }
        }
    }
    hienthi(mangba, Solan);
    // ngược lại
    for (byte z = 0; z < 8; z++)
    { // Z là số lần dời
        for (byte i = 1; i < 8 - z; i++)
        { // i là số công việc phải làm trong 1 lần dời
            for (byte x = 0; x < 8; x++)
            {
                for (byte y = 0; y < 8; y++)
                {
                    if (truc == 'X')
                    {
                        if (mangba[7 - i][x][y] == 1)
                        {
                            mangba[7 - i + 1][x][y] = 1;
                            mangba[7 - i][x][y] = 0;
                        }
                    }
                    else if (truc == 'Y')
                    {
                        if (mangba[x][7 - i][y] == 1)
                        {
                            mangba[x][7 - i + 1][y] = 1;
                            mangba[x][7 - i][y] = 0;
                        }
                    }
                    else
                    {
                        if (mangba[x][y][7 - i] == 1)
                        {
                            mangba[x][y][7 - i + 1] = 1;
                            mangba[x][y][7 - i] = 0;
                        }
                    }
                }
            }
        }
        hienthi(mangba, Solan + 4); // lấy Solan=4 rồi cộng thêm 4 nữa vì lúc chọn 8 vị trí ngẫu
                                    // nhiên mình đã cho hiển thi hết 8 lần
    }
}

void dich74hc595(byte a){
    if (a==0) {
        digitalWrite(A1, LOW);
        digitalWrite(A3, HIGH);
        digitalWrite(A3, LOW);
    } else if(a==1) {
        digitalWrite(A1, HIGH);
        digitalWrite(A3, HIGH);
        digitalWrite(A3, LOW);
    }
}

void mo74hc595() {
    digitalWrite(A2, HIGH);
    digitalWrite(A2, LOW);
}

void reset() {
    for (byte t=0; t<64; t++) {
        dich74hc595(0);
    }
    mo74hc595();
}

void hienthi(byte mangba[8][8][8], byte Solan){
      for (byte t=0; t<Solan; t++) { // so 7 la thoi gian qua 1 tang
        //to chinh la toc do roi cua mua
        for (byte z=0; z<8; z++) {
          for (byte x=0; x<8; x++) {
            for (byte y=0; y<8; y++) {
              dich74hc595(mangba[x][y][z]);
            }
          }
          mo74hc595();
          digitalWrite(Tangz[z], HIGH);   
          reset();
          digitalWrite(Tangz[z], LOW);
        }
      }
}
