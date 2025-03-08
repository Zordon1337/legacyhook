using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Loader
{
    public partial class Form1: Form
    {
        int pid = 0;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            new Thread(() =>
            {
                Thread.CurrentThread.IsBackground = true;

                while (true)
                {
                    try { if (Process.GetProcessesByName("csgo")[0] == null) continue; pid = Process.GetProcessesByName("csgo")[0].Id; } catch(IndexOutOfRangeException) 
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            label2.Text = "PID: 0";
                            label2.ForeColor = Color.Red;
                        }); continue; 
                    }

                    

                    this.Invoke((MethodInvoker)delegate
                    {
                        label2.Text = "PID: " + pid;
                        label2.ForeColor = Color.Green;
                    });
                }
            }).Start();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (pid == 0) MessageBox.Show("Launch game first!");
            var dllpath = Application.StartupPath + "\\legacyhook.dll";
            var handle = Imports.OpenProcess((int)(Imports.PROCESS_ACCESS_FLAGS.PROCESS_VM_READ | Imports.PROCESS_ACCESS_FLAGS.PROCESS_VM_WRITE | Imports.PROCESS_ACCESS_FLAGS.PROCESS_VM_OPERATION), false, pid);
            var buffer = Imports.VirtualAllocEx(handle, 0, dllpath.Length + 1, (int)Imports.MEMORY_ACCESS_FLAGS.MEM_COMMIT, (int)Imports.PAGE_ACCESS_FLAGS.PAGE_READWRITE);

            Imports.WriteProcessMemory(handle, buffer, Marshal.StringToHGlobalAnsi(dllpath), dllpath.Length + 1, 0);
            Imports.WaitForSingleObject(Imports.CreateRemoteThread(handle, IntPtr.Zero, 0, Imports.GetProcAddress(Imports.LoadLibraryA("kernel32.dll"), "LoadLibraryA"), buffer, 0, 0), -1);
            Imports.VirtualFreeEx(handle, buffer, 0, (int)Imports.MEMORY_ACCESS_FLAGS.MEM_RELEASE);
            new Thread(() => { MessageBox.Show("Loaded!", "Legacyhook Loader"); }).Start();
            Application.Exit();
        }
    }

    public class Imports
    {
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(
            int dwDesiredAccess,
            bool bInheritHandle,
            int dwProcessId
        );

        [DllImport("kernel32.dll")]
        public static extern IntPtr LoadLibraryA(
            string lpLibFileName
        );

        [DllImport("kernel32.dll")]
        public static extern IntPtr GetProcAddress(
            IntPtr hModule,
            string lpProcName
        );

        [DllImport("kernel32.dll")]
        public static extern IntPtr CreateRemoteThread(
            IntPtr hProcess,
            IntPtr lpThreadAttributes,
            int dwStackSize,
            IntPtr lpStartAddress,
            IntPtr lpParameter,
            int dwCreationFlags,
            int lpThreadId
        );

        [DllImport("kernel32.dll")]
        public static extern int WaitForSingleObject(
            IntPtr hProcess,
            int dwMilliseconds
        );

        [DllImport("kernel32.dll")]
        public static extern IntPtr VirtualAllocEx(
            IntPtr hProcess,
            int lpAddress,
            int dwSize,
            int flAllocationType,
            int flProtect
        );

        [DllImport("kernel32.dll")]
        public static extern bool VirtualFreeEx(
            IntPtr hProcess,
            IntPtr lpAddress,
            int dwSize,
            int dwFreeType
        );

        [DllImport("kernel32.dll")]
        public static extern bool WriteProcessMemory(
            IntPtr hProcess,
            IntPtr lpBaseAddress,
            IntPtr lpBuffer,
            int nSize,
            int lpNumberOfBytesWritten
        );

        [Flags]
        public enum PROCESS_ACCESS_FLAGS
        {
            PROCESS_VM_READ = 0x0010,
            PROCESS_VM_WRITE = 0x0020,
            PROCESS_VM_OPERATION = 0x0008,
        }

        [Flags]
        public enum MEMORY_ACCESS_FLAGS
        {
            MEM_COMMIT = 0x00001000,
            MEM_RELEASE = 0x00008000
        }

        [Flags]
        public enum PAGE_ACCESS_FLAGS
        {
            PAGE_READWRITE = 0x04
        }
    }
}
