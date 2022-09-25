import java.io.FileOutputStream;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Random;
import java.util.Scanner;
import java.util.Random;
public class Operate {
    public static void write(String str) throws IOException {//写入txt文件
        String filepath = "Answers.txt";
       // String filepath = "F:\\java\\homework1\\src\\Answers.txt";
        FileOutputStream fileOutputStream = new FileOutputStream(filepath,true);
        fileOutputStream.write(str.getBytes());
        fileOutputStream.write('\n');
        fileOutputStream.close();

    }
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        int[] a = new int[n];
        int[] b = new int[n];
        int[] c = new int[n];//用于运算的三个数字

        int[] f1 = new int[n];
        int[] f2 = new int[n];//用于判断运算符，0，1分别表示加减
        int[] count = new int[n];//用于计算运算符个数，0-1表示一个运算符，2表示两个，比例为2：1
        char[] ch1 = new char[n];
        char[] ch2 = new char[n];
        String[] str = new String[n];//用于存储运算式
        int[] ans = new int[n];//用于存储答案

        Random r = new Random();
        for(int i = 0;i<n;i++){
            a[i] = r.nextInt(100);
            b[i] = r.nextInt(100);
            c[i] = r.nextInt(100);
            f1[i] = r.nextInt(2);
            f2[i] = r.nextInt(2);
            count[i] = r.nextInt(3);
        }
        for(int i = 0;i<n;i++){
            if(f1[i] == 0) {ch1[i] ='+';}
            if(f2[i] == 0) {ch2[i] ='+';}
            if(f1[i] == 1) {ch1[i] ='-';}
            if(f2[i] == 1) {ch2[i] ='-';}
        }

        Calendar calendar = Calendar.getInstance();
        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        //System.out.println(formatter.format(calendar.getTime()));
        String time =formatter.format(calendar.getTime()).toString();//获取当时的时间来记录存储时间
        try {//记录操作时间
            write(time);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        for(int i = 0;i<n;i++) {
            if (count[i] == 2) {
                str[i] = i + 1 + ".四则运算题目" + (i + 1) + ": " + a[i] + "" + ch1[i] + "" + b[i] + "" + ch2[i] + "" + c[i];
                if (ch1[i] == '+' && ch2[i] == '+') ans[i] = a[i] + b[i] + c[i];
                if (ch1[i] == '+' && ch2[i] == '-') ans[i] = a[i] + b[i] - c[i];
                if (ch1[i] == '-' && ch2[i] == '-') ans[i] = a[i] - b[i] - c[i];
                if (ch1[i] == '-' && ch2[i] == '+') ans[i] = a[i] - b[i] + c[i];

            } else {
                str[i] = i + 1 + ".四则运算题目" + (i + 1) + ": " + a[i] + "" + ch1[i] + "" + b[i];
                if (ch1[i] == '+') ans[i] = a[i] + b[i];
                else ans[i] = a[i] - b[i];

            }

            str[i] = str[i]+"="+String.valueOf(ans[i]);

            try {
                write(str[i]);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }

        }



//
//        for(int i = 0;i<n;i++){
//            System.out.println(ch1[i]+""+ch2[i]);
//        }



    }


}
