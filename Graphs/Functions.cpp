#include "Functions.h"

void sort(int* t, int k) {
	bool swapped;
	for (int i = 0; i < k - 1; i++) {
		swapped = false;
		for (int j = 0; j < k - i - 1; j++) {
			if (t[j] > t[j + 1]) {
				int temp = t[j];
				t[j] = t[j + 1];
				t[j + 1] = temp;
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

bool Duplicate(int a[], int size, int num) {
	for (int i = 0; i < size; ++i) {
		if (num == a[i]) {
			return true;
		}
	}
	return false;
}

bool AllZeroes(int** arr, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (arr[i][j] != 0) {
				return false;
			}
		}
	}
	return true;
}

void MultiplyMatrices(int** a, int** b, int** result, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			result[i][j] = 0;
			for (int k = 0; k < size; ++k) {
				result[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}

void NewMatrix(int count, int** new_array, int** result, int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			new_array[i][j + count * size] = result[i][j];
		}
	}
}


/*using System;
using System.Diagnostics;
using System.Net;
using System.Reflection;
using System.Windows.Forms;

namespace MyApp
{
	public partial class MainForm : Form
	{
		private const string UpdateServerUrl = "http://your-update-server.com/updates/";

		public MainForm()
		{
			InitializeComponent();
		}

		private void MainForm_Load(object sender, EventArgs e)
		{
			CheckForUpdates();
		}

		private void CheckForUpdates()
		{
			try
			{
				Version currentVersion = Assembly.GetExecutingAssembly().GetName().Version;

				using (WebClient client = new WebClient())
				{
					string updateInfo = client.DownloadString(UpdateServerUrl + "version.txt");
					Version latestVersion = new Version(updateInfo);

					if (latestVersion > currentVersion)
					{
						DialogResult result = MessageBox.Show("New version available. Do you want to update?",
							"Update Available", MessageBoxButtons.YesNo, MessageBoxIcon.Information);

						if (result == DialogResult.Yes)
						{
							DownloadUpdate();
						}
					}
					else
					{
						MessageBox.Show("You have the latest version.", "No Updates", MessageBoxButtons.OK, MessageBoxIcon.Information);
					}
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show("Error checking for updates: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}

		private void DownloadUpdate()
		{
			try
			{
				using (WebClient client = new WebClient())
				{
					string updateFileUrl = UpdateServerUrl + "MyAppSetup.exe"; // Replace with actual setup file name
					string tempFilePath = System.IO.Path.GetTempFileName();

					client.DownloadFile(updateFileUrl, tempFilePath);

					Process.Start(tempFilePath); // Launch the installer
					Application.Exit(); // Exit the current version
				}
			}
			catch (Exception ex)
			{
				MessageBox.Show("Error downloading update: " + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
			}
		}
	}
}
*/