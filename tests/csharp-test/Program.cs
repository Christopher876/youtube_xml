using System;
using System.Runtime.InteropServices;

namespace csharp_test
{
    class Program
    {
        [DllImport("../../build/libtest.so")]
        static extern int hello();

        static void Main(string[] args)
        {
            hello();
        }
    }
}
