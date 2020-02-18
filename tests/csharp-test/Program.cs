using System;
using System.Runtime.InteropServices;

namespace csharp_test
{
    class Program
    {
        [DllImport("../../build/libtest.so")]
        static extern int hello(string url);

        [DllImport("../../build/libtest.so")]
        static extern IntPtr test_ip();

        static void Main(string[] args)
        {
            Console.WriteLine("Testing Youtube XML C++ Library");
            //hello("https://www.youtube.com/feeds/videos.xml?channel_id=UCS0N5baNlQWJCUrhCEo8WlA");
            var c = test_ip();
            var d = Marshal.PtrToStringUTF8(c);
            Console.WriteLine(d);
        }
    }
}
