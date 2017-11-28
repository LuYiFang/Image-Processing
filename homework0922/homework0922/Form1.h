#pragma once
#include<time.h>
#include <cstdlib> 
#include<math.h>


struct COMPLEX1{
	double real;
	double imag;
};

namespace homework0922 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	int his[256] = {0};

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
			int** arrayR, **arrayG,** arrayB, **arrayGray ;
			int imW, imH, MaskSize;
	private: System::Windows::Forms::ToolStripMenuItem^  frecrencyFilteringToolStripMenuItem;
	public: 
	private: System::Windows::Forms::ToolStripButton^  toolStripButton18;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton19;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::RadioButton^  radioButton6;
	private: System::Windows::Forms::RadioButton^  radioButton5;
	private: System::Windows::Forms::CheckBox^  checkBox2;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  hFToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton20;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton21;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton22;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton23;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton24;
			 int T;

			int binary(int i){return (i < 128)?1:0;}
			int signal(int i){return (i % 2 == 0)?1:-1;}

			void DFT(int dir, int n, double *real1, double *image1){
				double pi, c, s, d, *real2, *image2;
				real2 = new double[n];
				image2 = new double[n];
				pi = 4.0 * atan(1.0);
				for (int i = 0; i<n; i++) {
					real2[i] = 0;
					image2[i] = 0;
					d = -dir * 2.0 * pi * (double)i / (double)n;
					for (int k = 0; k<n; k++) {
						c = cos(k * d);
						s = sin(k * d);
						real2[i] += (real1[k] * c - image1[k] * s);
						image2[i] += (real1[k] * s + image1[k] * c);
					}//for k
				}//for i

				/* Copy the data back */
				if (dir == 1) { //DFT
					for (int i = 0; i<n; i++) {
						real1[i] = real2[i] / (double)n;
						image1[i] = image2[i] / (double)n; }//for i
					}//if (dir == 1)
				else { //else i.e. (dir == -1), IDFT
					for (int i = 0; i<n; i++) {
						real1[i] = real2[i];
						image1[i] = image2[i]; 
					}//for i
				}//else i.e. (dir == -1)
				delete[] image2;
				delete[] real2;
		}//DFT

			void DFT2d(COMPLEX1 **c,int n,int dir){
				double *real,*image;
				real = new double[n];
				image = new double[n];
				for(int j = 0;j < n;j++){// row
					for(int i = 0;i < n;i++){
						real[i] = c[i][j].real;
						image[i] = c[i][j].imag;
					}//for i
					
					
					 DFT1(dir,n,real,image);
					for(int i = 0;i < n;i++){
						 c[i][j].real = real[i];
						 c[i][j].imag = image[i];
					}//for i
				}//for j

				for(int i = 0;i < n;i++){//collumn
					for(int j = 0;j < n;j++){
						real[j] = c[i][j].real;
						image[j] = c[i][j].imag;
					}//for i
					
					DFT1(dir,n,real,image);
					for(int j = 0;j < n;j++){
						 if(dir == 1){
							c[i][j].real = real[j]*n;
							c[i][j].imag = image[j]*n;
						}else {
							c[i][j].real = real[j]/n;
							c[i][j].imag = image[j]/n;
						}
					}//for i
				}//for j
				delete[] real;
				delete[] image;
			}



			//FFT
			void DFT1(int dir, int n, double *real1, double *image1){
				double pi, **c, d, *real2, *image2;
				double **s;
				int i,k;
				real2 = new double[n];
				image2 = new double[n];
				pi = 4.0 * atan(1.0);
				c = new double*[n];
				s = new double*[n];
				for( i = 0;i < n;i++){
					c[i] = new double[n];	
				}
				for( i = 0;i < n;i++)
					s[i] = new double[n];

				int m = n/2;
				c[0][0] = 1.0;
				s[0][0] = 0.0;
				for( i = 1;i < n;i++){
					c[i][0] = 1.0;
					s[i][0] = 0.0;
				}
				for( i = 1;i < n;i++){
					c[0][i] = 1.0;
					s[0][i] = 0.0;
				}
				
				for( i = 1;i < n;i++){
					c[m][i] = signal(i);
					s[m][i] = 0.0;
				}
				for( i = 1;i < n;i++){
					c[i][m] = signal(i);
					s[i][m] = 0.0;
				}

				d = -dir*2.0*pi/n;
				for( k = 1;k < m;k++){
					c[1][k] = cos(k * d);
					s[1][k] = sin(k * d);
					c[1][n-k] = c[1][k];
					s[1][n-k] = -s[1][k];
					c[n-k][1] = c[1][k];
					s[n-k][1] = -s[1][k];
					c[n-1][n-k] = c[1][k];
					s[n-1][n-k] = s[1][k];
				}

				for(i = 2;i < m;i++){
					for(k = 1;k < m;k++){
						c[i][k] = c[1][i * k % n];
						s[i][k] = s[1][i * k % n];
						c[i][n-k] = c[i][k];
						s[i][n-k] = -s[i][k];
						c[n-k][i] = c[i][k];
						s[n-k][i] = -s[i][k];
						c[n-i][n-k] = c[i][k];
						s[n-i][n-k] = s[i][k];
					}
				}

				for (int i = 0; i<n; i++) {
					real2[i] = 0;
					image2[i] = 0;
					for (int k = 0; k<n; k++) {
						real2[i] += (real1[k] * c[i][k] - image1[k] * s[i][k]);
						image2[i] += (real1[k] * s[i][k] + image1[k] * c[i][k]);
					}//for k
				}//for i

				/* Copy the data back */
				if (dir == 1) { //DFT
					for (int i = 0; i<n; i++) {
						real1[i] = real2[i] / (double)n;
						image1[i] = image2[i] / (double)n; }//for i
					}//if (dir == 1)
				else { //else i.e. (dir == -1), IDFT
					for (int i = 0; i<n; i++) {
						real1[i] = real2[i];
						image1[i] = image2[i]; 
					}//for i
				}//else i.e. (dir == -1)
				delete[] image2;
				delete[] real2;
				for (int i = 0; i < n; i++)
					delete [] c[i];
				delete[] c;
				for (int i = 0; i < n; i++)
					delete [] s[i];
				delete[] s;
		}//DFT


	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton8;
	private: System::Windows::Forms::ToolStripMenuItem^  equlizeToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::RadioButton^  radioButton3;
	private: System::Windows::Forms::RadioButton^  radioButton2;
	private: System::Windows::Forms::RadioButton^  radioButton1;
	private: System::Windows::Forms::RadioButton^  radioButton4;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  maskToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  noiseToolStripMenuItem;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton9;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton10;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton11;
	private: System::Windows::Forms::ToolStripMenuItem^  binarizationToolStripMenuItem;
	private: System::Windows::Forms::HScrollBar^  hScrollBar1;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton12;
	private: System::Windows::Forms::CheckBox^  checkBox1;
	private: System::Windows::Forms::ToolStripMenuItem^  otsuToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton13;
	private: System::Windows::Forms::ToolStripMenuItem^  sobToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton14;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton15;
	private: System::Windows::Forms::ToolStripMenuItem^  thinningToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dFTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  fFTToolStripMenuItem;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton16;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton17;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label9;


public:
	PixelFormat myPixelFormat;
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	 protected:
	
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveAsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  invrseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  grayToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;
	




	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveAsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->invrseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->grayToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->equlizeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->maskToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->noiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->binarizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->otsuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sobToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thinningToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fFTToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->frecrencyFilteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->hFToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton8 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton9 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton10 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton11 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton12 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton13 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton14 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton15 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton16 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton17 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton19 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton18 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton20 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton21 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton22 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton23 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->radioButton4 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton3 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->radioButton6 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->toolStripButton24 = (gcnew System::Windows::Forms::ToolStripButton());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->BeginInit();
			this->toolStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Sanpya", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(933, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->openToolStripMenuItem, 
				this->saveAsToolStripMenuItem, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveAsToolStripMenuItem
			// 
			this->saveAsToolStripMenuItem->Enabled = false;
			this->saveAsToolStripMenuItem->Name = L"saveAsToolStripMenuItem";
			this->saveAsToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->saveAsToolStripMenuItem->Text = L"Save as ";
			this->saveAsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveAsToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(119, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(15) {this->invrseToolStripMenuItem, 
				this->grayToolStripMenuItem, this->undoToolStripMenuItem, this->histogramToolStripMenuItem, this->equlizeToolStripMenuItem, this->maskToolStripMenuItem, 
				this->noiseToolStripMenuItem, this->binarizationToolStripMenuItem, this->otsuToolStripMenuItem, this->sobToolStripMenuItem, this->thinningToolStripMenuItem, 
				this->dFTToolStripMenuItem, this->fFTToolStripMenuItem, this->frecrencyFilteringToolStripMenuItem, this->hFToolStripMenuItem});
			this->editToolStripMenuItem->Enabled = false;
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// invrseToolStripMenuItem
			// 
			this->invrseToolStripMenuItem->Name = L"invrseToolStripMenuItem";
			this->invrseToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->invrseToolStripMenuItem->Text = L"Inverse";
			this->invrseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::invrseToolStripMenuItem_Click);
			// 
			// grayToolStripMenuItem
			// 
			this->grayToolStripMenuItem->Name = L"grayToolStripMenuItem";
			this->grayToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->grayToolStripMenuItem->Text = L"Gray";
			this->grayToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::grayToolStripMenuItem_Click);
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->undoToolStripMenuItem->Text = L"Undo";
			this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::undoToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::histogramToolStripMenuItem_Click);
			// 
			// equlizeToolStripMenuItem
			// 
			this->equlizeToolStripMenuItem->Name = L"equlizeToolStripMenuItem";
			this->equlizeToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->equlizeToolStripMenuItem->Text = L"Equalization";
			this->equlizeToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::equlizeToolStripMenuItem_Click);
			// 
			// maskToolStripMenuItem
			// 
			this->maskToolStripMenuItem->Name = L"maskToolStripMenuItem";
			this->maskToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->maskToolStripMenuItem->Text = L"Mask";
			this->maskToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::maskToolStripMenuItem_Click);
			// 
			// noiseToolStripMenuItem
			// 
			this->noiseToolStripMenuItem->Name = L"noiseToolStripMenuItem";
			this->noiseToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->noiseToolStripMenuItem->Text = L"noise";
			this->noiseToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::noiseToolStripMenuItem_Click);
			// 
			// binarizationToolStripMenuItem
			// 
			this->binarizationToolStripMenuItem->Name = L"binarizationToolStripMenuItem";
			this->binarizationToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->binarizationToolStripMenuItem->Text = L"Binarization";
			this->binarizationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::binarizationToolStripMenuItem_Click);
			// 
			// otsuToolStripMenuItem
			// 
			this->otsuToolStripMenuItem->Name = L"otsuToolStripMenuItem";
			this->otsuToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->otsuToolStripMenuItem->Text = L"Otsu";
			this->otsuToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::otsuToolStripMenuItem_Click);
			// 
			// sobToolStripMenuItem
			// 
			this->sobToolStripMenuItem->Name = L"sobToolStripMenuItem";
			this->sobToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->sobToolStripMenuItem->Text = L"Sobel";
			this->sobToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::sobToolStripMenuItem_Click);
			// 
			// thinningToolStripMenuItem
			// 
			this->thinningToolStripMenuItem->Name = L"thinningToolStripMenuItem";
			this->thinningToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->thinningToolStripMenuItem->Text = L"Thinning";
			this->thinningToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::thinningToolStripMenuItem_Click);
			// 
			// dFTToolStripMenuItem
			// 
			this->dFTToolStripMenuItem->Name = L"dFTToolStripMenuItem";
			this->dFTToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->dFTToolStripMenuItem->Text = L"DFT";
			this->dFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::dFTToolStripMenuItem_Click);
			// 
			// fFTToolStripMenuItem
			// 
			this->fFTToolStripMenuItem->Name = L"fFTToolStripMenuItem";
			this->fFTToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->fFTToolStripMenuItem->Text = L"FFT";
			this->fFTToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::fFTToolStripMenuItem_Click);
			// 
			// frecrencyFilteringToolStripMenuItem
			// 
			this->frecrencyFilteringToolStripMenuItem->Name = L"frecrencyFilteringToolStripMenuItem";
			this->frecrencyFilteringToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->frecrencyFilteringToolStripMenuItem->Text = L"LF";
			this->frecrencyFilteringToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::frecrencyFilteringToolStripMenuItem_Click);
			// 
			// hFToolStripMenuItem
			// 
			this->hFToolStripMenuItem->Name = L"hFToolStripMenuItem";
			this->hFToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->hFToolStripMenuItem->Text = L"HF";
			this->hFToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::hFToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(28, 60);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(256, 256);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(335, 60);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(256, 256);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->Location = System::Drawing::Point(640, 60);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(256, 256);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 3;
			this->pictureBox3->TabStop = false;
			// 
			// toolStrip1
			// 
			this->toolStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(24) {this->toolStripButton1, 
				this->toolStripButton5, this->toolStripButton2, this->toolStripButton3, this->toolStripButton4, this->toolStripButton6, this->toolStripButton7, 
				this->toolStripButton8, this->toolStripButton9, this->toolStripButton10, this->toolStripButton11, this->toolStripButton12, this->toolStripButton13, 
				this->toolStripButton14, this->toolStripButton15, this->toolStripButton16, this->toolStripButton17, this->toolStripButton19, 
				this->toolStripButton18, this->toolStripButton20, this->toolStripButton21, this->toolStripButton22, this->toolStripButton23, 
				this->toolStripButton24});
			this->toolStrip1->Location = System::Drawing::Point(0, 24);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Padding = System::Windows::Forms::Padding(0, 0, 2, 0);
			this->toolStrip1->Size = System::Drawing::Size(933, 27);
			this->toolStrip1->TabIndex = 4;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(24, 24);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->Click += gcnew System::EventHandler(this, &Form1::toolStripButton1_Click);
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Enabled = false;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(24, 24);
			this->toolStripButton2->Text = L"Inserve";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &Form1::toolStripButton2_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton3->Enabled = false;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(24, 24);
			this->toolStripButton3->Text = L"Gray";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &Form1::toolStripButton3_Click);
			// 
			// toolStripButton4
			// 
			this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton4->Enabled = false;
			this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton4.Image")));
			this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton4->Name = L"toolStripButton4";
			this->toolStripButton4->Size = System::Drawing::Size(24, 24);
			this->toolStripButton4->Text = L"Save";
			this->toolStripButton4->Click += gcnew System::EventHandler(this, &Form1::toolStripButton4_Click);
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton6->Enabled = false;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(24, 24);
			this->toolStripButton6->Text = L"Undo";
			this->toolStripButton6->Click += gcnew System::EventHandler(this, &Form1::toolStripButton6_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton7->Enabled = false;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(24, 24);
			this->toolStripButton7->Text = L"Histogram";
			this->toolStripButton7->Click += gcnew System::EventHandler(this, &Form1::toolStripButton7_Click);
			// 
			// toolStripButton8
			// 
			this->toolStripButton8->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton8->Enabled = false;
			this->toolStripButton8->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton8.Image")));
			this->toolStripButton8->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton8->Name = L"toolStripButton8";
			this->toolStripButton8->Size = System::Drawing::Size(24, 24);
			this->toolStripButton8->Text = L"Equalization";
			this->toolStripButton8->Click += gcnew System::EventHandler(this, &Form1::toolStripButton8_Click);
			// 
			// toolStripButton9
			// 
			this->toolStripButton9->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton9->Enabled = false;
			this->toolStripButton9->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton9.Image")));
			this->toolStripButton9->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton9->Name = L"toolStripButton9";
			this->toolStripButton9->Size = System::Drawing::Size(24, 24);
			this->toolStripButton9->Text = L"Noise";
			this->toolStripButton9->Click += gcnew System::EventHandler(this, &Form1::toolStripButton9_Click);
			// 
			// toolStripButton10
			// 
			this->toolStripButton10->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton10->Enabled = false;
			this->toolStripButton10->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton10.Image")));
			this->toolStripButton10->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton10->Name = L"toolStripButton10";
			this->toolStripButton10->Size = System::Drawing::Size(24, 24);
			this->toolStripButton10->Text = L"Average";
			this->toolStripButton10->Click += gcnew System::EventHandler(this, &Form1::toolStripButton10_Click);
			// 
			// toolStripButton11
			// 
			this->toolStripButton11->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton11->Enabled = false;
			this->toolStripButton11->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton11.Image")));
			this->toolStripButton11->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton11->Name = L"toolStripButton11";
			this->toolStripButton11->Size = System::Drawing::Size(24, 24);
			this->toolStripButton11->Text = L"Middle";
			this->toolStripButton11->Click += gcnew System::EventHandler(this, &Form1::toolStripButton11_Click);
			// 
			// toolStripButton12
			// 
			this->toolStripButton12->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton12->Enabled = false;
			this->toolStripButton12->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton12.Image")));
			this->toolStripButton12->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton12->Name = L"toolStripButton12";
			this->toolStripButton12->Size = System::Drawing::Size(24, 24);
			this->toolStripButton12->Text = L"Binarization";
			this->toolStripButton12->Click += gcnew System::EventHandler(this, &Form1::toolStripButton12_Click);
			// 
			// toolStripButton13
			// 
			this->toolStripButton13->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton13->Enabled = false;
			this->toolStripButton13->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton13.Image")));
			this->toolStripButton13->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton13->Name = L"toolStripButton13";
			this->toolStripButton13->Size = System::Drawing::Size(24, 24);
			this->toolStripButton13->Text = L"Otsu";
			this->toolStripButton13->Click += gcnew System::EventHandler(this, &Form1::toolStripButton13_Click);
			// 
			// toolStripButton14
			// 
			this->toolStripButton14->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton14->Enabled = false;
			this->toolStripButton14->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton14.Image")));
			this->toolStripButton14->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton14->Name = L"toolStripButton14";
			this->toolStripButton14->Size = System::Drawing::Size(24, 24);
			this->toolStripButton14->Text = L"Sobel";
			this->toolStripButton14->Click += gcnew System::EventHandler(this, &Form1::toolStripButton14_Click);
			// 
			// toolStripButton15
			// 
			this->toolStripButton15->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton15->Enabled = false;
			this->toolStripButton15->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton15.Image")));
			this->toolStripButton15->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton15->Name = L"toolStripButton15";
			this->toolStripButton15->Size = System::Drawing::Size(24, 24);
			this->toolStripButton15->Text = L"Thinning";
			this->toolStripButton15->Click += gcnew System::EventHandler(this, &Form1::toolStripButton15_Click);
			// 
			// toolStripButton16
			// 
			this->toolStripButton16->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton16->Enabled = false;
			this->toolStripButton16->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton16.Image")));
			this->toolStripButton16->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton16->Name = L"toolStripButton16";
			this->toolStripButton16->Size = System::Drawing::Size(24, 24);
			this->toolStripButton16->Text = L"DFT";
			this->toolStripButton16->Click += gcnew System::EventHandler(this, &Form1::toolStripButton16_Click);
			// 
			// toolStripButton17
			// 
			this->toolStripButton17->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton17->Enabled = false;
			this->toolStripButton17->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton17.Image")));
			this->toolStripButton17->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton17->Name = L"toolStripButton17";
			this->toolStripButton17->Size = System::Drawing::Size(24, 24);
			this->toolStripButton17->Text = L"FFT";
			this->toolStripButton17->Click += gcnew System::EventHandler(this, &Form1::toolStripButton17_Click);
			// 
			// toolStripButton19
			// 
			this->toolStripButton19->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton19->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton19.Image")));
			this->toolStripButton19->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton19->Name = L"toolStripButton19";
			this->toolStripButton19->Size = System::Drawing::Size(24, 24);
			this->toolStripButton19->Text = L"toolStripButton19";
			this->toolStripButton19->Click += gcnew System::EventHandler(this, &Form1::toolStripButton19_Click);
			// 
			// toolStripButton18
			// 
			this->toolStripButton18->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton18->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton18.Image")));
			this->toolStripButton18->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton18->Name = L"toolStripButton18";
			this->toolStripButton18->Size = System::Drawing::Size(24, 24);
			this->toolStripButton18->Text = L"toolStripButton18";
			this->toolStripButton18->Click += gcnew System::EventHandler(this, &Form1::toolStripButton18_Click);
			// 
			// toolStripButton20
			// 
			this->toolStripButton20->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton20->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton20.Image")));
			this->toolStripButton20->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton20->Name = L"toolStripButton20";
			this->toolStripButton20->Size = System::Drawing::Size(24, 24);
			this->toolStripButton20->Text = L"toolStripButton20";
			this->toolStripButton20->Click += gcnew System::EventHandler(this, &Form1::toolStripButton20_Click);
			// 
			// toolStripButton21
			// 
			this->toolStripButton21->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton21->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton21.Image")));
			this->toolStripButton21->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton21->Name = L"toolStripButton21";
			this->toolStripButton21->Size = System::Drawing::Size(24, 24);
			this->toolStripButton21->Text = L"Bilinear";
			this->toolStripButton21->Click += gcnew System::EventHandler(this, &Form1::toolStripButton21_Click);
			// 
			// toolStripButton22
			// 
			this->toolStripButton22->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton22->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton22.Image")));
			this->toolStripButton22->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton22->Name = L"toolStripButton22";
			this->toolStripButton22->Size = System::Drawing::Size(24, 24);
			this->toolStripButton22->Text = L"Bicubic";
			this->toolStripButton22->Click += gcnew System::EventHandler(this, &Form1::toolStripButton22_Click);
			// 
			// toolStripButton23
			// 
			this->toolStripButton23->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton23->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton23.Image")));
			this->toolStripButton23->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton23->Name = L"toolStripButton23";
			this->toolStripButton23->Size = System::Drawing::Size(24, 24);
			this->toolStripButton23->Text = L"Rotate";
			this->toolStripButton23->Click += gcnew System::EventHandler(this, &Form1::toolStripButton23_Click);
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(24, 24);
			this->toolStripButton5->Text = L"Exit";
			this->toolStripButton5->Click += gcnew System::EventHandler(this, &Form1::toolStripButton5_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(112, 323);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(72, 25);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Original";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(415, 323);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(90, 25);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Histogram";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(746, 323);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 25);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Target";
			// 
			// comboBox1
			// 
			this->comboBox1->Enabled = false;
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(4) {L"R", L"G", L"B", L"Y"});
			this->comboBox1->Location = System::Drawing::Point(396, 369);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 28);
			this->comboBox1->TabIndex = 8;
			this->comboBox1->Text = L"Color";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::histogramToolStripMenuItem_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(290, 49);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 17);
			this->label4->TabIndex = 9;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(332, 323);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(0, 17);
			this->label5->TabIndex = 10;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(591, 323);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(0, 17);
			this->label6->TabIndex = 11;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->label9);
			this->groupBox1->Controls->Add(this->radioButton4);
			this->groupBox1->Controls->Add(this->radioButton3);
			this->groupBox1->Controls->Add(this->radioButton2);
			this->groupBox1->Controls->Add(this->radioButton1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox1->Location = System::Drawing::Point(640, 354);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(256, 94);
			this->groupBox1->TabIndex = 12;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Mask Size";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(128, 60);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 23);
			this->textBox2->TabIndex = 5;
			this->textBox2->Text = L"1.0";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(21, 63);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(101, 17);
			this->label9->TabIndex = 4;
			this->label9->Text = L"Signal : (k)(FT_c)";
			// 
			// radioButton4
			// 
			this->radioButton4->AutoSize = true;
			this->radioButton4->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton4->Location = System::Drawing::Point(205, 25);
			this->radioButton4->Name = L"radioButton4";
			this->radioButton4->Size = System::Drawing::Size(45, 21);
			this->radioButton4->TabIndex = 3;
			this->radioButton4->TabStop = true;
			this->radioButton4->Text = L"9x9";
			this->radioButton4->UseVisualStyleBackColor = true;
			// 
			// radioButton3
			// 
			this->radioButton3->AutoSize = true;
			this->radioButton3->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton3->Location = System::Drawing::Point(136, 25);
			this->radioButton3->Name = L"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(47, 21);
			this->radioButton3->TabIndex = 2;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = L"7x7";
			this->radioButton3->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton2->Location = System::Drawing::Point(71, 25);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(47, 21);
			this->radioButton2->TabIndex = 1;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"5x5";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->radioButton1->Location = System::Drawing::Point(10, 25);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(45, 21);
			this->radioButton1->TabIndex = 0;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"3x3";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &Form1::radioButton1_CheckedChanged);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(98, 358);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 23);
			this->textBox1->TabIndex = 13;
			this->textBox1->Text = L"5";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(42, 360);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(50, 17);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Noise(%)";
			// 
			// hScrollBar1
			// 
			this->hScrollBar1->LargeChange = 1;
			this->hScrollBar1->Location = System::Drawing::Point(344, 433);
			this->hScrollBar1->Maximum = 256;
			this->hScrollBar1->Name = L"hScrollBar1";
			this->hScrollBar1->Size = System::Drawing::Size(227, 18);
			this->hScrollBar1->TabIndex = 15;
			this->hScrollBar1->Value = 128;
			this->hScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Form1::hScrollBar1_Scroll);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(354, 406);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(79, 17);
			this->label8->TabIndex = 16;
			this->label8->Text = L"Threshold:128";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 8.999999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->checkBox1->Location = System::Drawing::Point(475, 406);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(54, 21);
			this->checkBox1->TabIndex = 17;
			this->checkBox1->Text = L"Show";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->checkBox2);
			this->groupBox2->Controls->Add(this->textBox4);
			this->groupBox2->Controls->Add(this->label11);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label10);
			this->groupBox2->Controls->Add(this->radioButton6);
			this->groupBox2->Controls->Add(this->radioButton5);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 12));
			this->groupBox2->Location = System::Drawing::Point(28, 390);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(200, 67);
			this->groupBox2->TabIndex = 18;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Frequency Filter";
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->checkBox2->Location = System::Drawing::Point(150, 43);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(43, 21);
			this->checkBox2->TabIndex = 6;
			this->checkBox2->Text = L"abs";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->textBox4->Location = System::Drawing::Point(106, 41);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(24, 23);
			this->textBox4->TabIndex = 5;
			this->textBox4->Text = L"1";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->label11->Location = System::Drawing::Point(87, 44);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(16, 17);
			this->label11->TabIndex = 4;
			this->label11->Text = L"n:";
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->textBox3->Location = System::Drawing::Point(34, 41);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(36, 23);
			this->textBox3->TabIndex = 3;
			this->textBox3->Text = L"15.0";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->label10->Location = System::Drawing::Point(6, 45);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(24, 17);
			this->label10->TabIndex = 2;
			this->label10->Text = L"D0:";
			// 
			// radioButton6
			// 
			this->radioButton6->AutoSize = true;
			this->radioButton6->Checked = true;
			this->radioButton6->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->radioButton6->Location = System::Drawing::Point(89, 20);
			this->radioButton6->Name = L"radioButton6";
			this->radioButton6->Size = System::Drawing::Size(89, 21);
			this->radioButton6->TabIndex = 1;
			this->radioButton6->TabStop = true;
			this->radioButton6->Text = L"Butterworth";
			this->radioButton6->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9));
			this->radioButton5->Location = System::Drawing::Point(6, 21);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(51, 21);
			this->radioButton5->TabIndex = 0;
			this->radioButton5->Text = L"ideal";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox6);
			this->groupBox3->Controls->Add(this->label13);
			this->groupBox3->Controls->Add(this->textBox5);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->groupBox3->Location = System::Drawing::Point(640, 466);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(256, 85);
			this->groupBox3->TabIndex = 19;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Geometry Transform";
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox6->Location = System::Drawing::Point(111, 57);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(100, 24);
			this->textBox6->TabIndex = 3;
			this->textBox6->Text = L"45.0";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(43, 57);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(43, 18);
			this->label13->TabIndex = 2;
			this->label13->Text = L"Rotate";
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox5->Location = System::Drawing::Point(111, 18);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(100, 24);
			this->textBox5->TabIndex = 1;
			this->textBox5->Text = L"2.0";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"AR CHRISTY", 9.749999F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(43, 21);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(38, 18);
			this->label12->TabIndex = 0;
			this->label12->Text = L"Scale";
			// 
			// toolStripButton24
			// 
			this->toolStripButton24->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton24->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton24.Image")));
			this->toolStripButton24->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->toolStripButton24->Name = L"toolStripButton24";
			this->toolStripButton24->Size = System::Drawing::Size(24, 24);
			this->toolStripButton24->Text = L"toolStripButton24";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(933, 564);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->hScrollBar1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Image Processing";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox3))->EndInit();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 openFileDialog1->Filter = "Bitmap Image|*.bmp|AllFiles|*.*";
				if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					pictureBox1->ImageLocation= openFileDialog1->FileName;
				} else {
				// open image error
				}
				Bitmap^ myBitmap= gcnew Bitmap(pictureBox1->ImageLocation);
				imW= myBitmap->Width;
				imH= myBitmap->Height;
				myPixelFormat= myBitmap->PixelFormat;
				// Lock the bitmap's bits.
				Rectangle rect= Rectangle(0,0,imW,imH);
				BitmapData^ bmpData= myBitmap->LockBits( rect, ImageLockMode::ReadWrite, myBitmap->PixelFormat);
				int ByteOfSkip= bmpData->Stride -bmpData->Width * 3;

			 unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;
			if (myBitmap->PixelFormat== PixelFormat::Format24bppRgb){
				//new a array[Height][Width] space
				arrayB= new int*[imH];
				for (int i = 0; i < imH; i++)
					arrayB[i] = new int[imW];
					arrayG= new int*[imH];
				for (int i = 0; i < imH; i++)
					arrayG[i] = new int[imW];
					arrayR= new int*[imH];
				for (int i = 0; i < imH; i++)
					arrayR[i] = new int[imW];
					arrayGray= new int*[imH];
				for (int i = 0; i < imH; i++)
					arrayGray[i] = new int[imW];
				for (int y = 0; y < imH; y++){
					for (int x = 0; x < imW; x++){
						arrayB[x][y] = (int)p[index+0];
						arrayG[x][y] = (int)p[index+1];
						arrayR[x][y] = (int)p[index+2];
						//arrayGray[i] = (int)(0.299*arrayR[y][x] + 0.587*arrayG[y][x] + 0.114*arrayB[y][x] + 0.5);
						arrayGray[x][y] = (int)((arrayB[x][y] + arrayG[x][y] + arrayR[x][y])/3.0 + 0.5);
						index += 3; }//for x
						index += ByteOfSkip; // 跳過剩下的Padding bytes
						}//for y
					}//if
			else if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed){
			//new a array[Height][Width] space
				arrayGray= new int*[imH];
				for (int i = 0; i < imH; i++)
					arrayGray[i] = new int[imW];

				for (int y = 0; y < imH; y++){
					for (int x = 0; x < imW; x++){
						arrayGray[x][y] = (int)p[index++];
					}//for x 
					//Gray Image無Padding bytes
				}//for y
			}//else
					// Unlock the bits.
				myBitmap->UnlockBits( bmpData);// Unlock the bits.
				editToolStripMenuItem->Enabled = true;
				toolStripButton2->Enabled = true;
				toolStripButton3->Enabled = true;
				toolStripButton4->Enabled = true;
				toolStripButton5->Enabled = true;
				toolStripButton6->Enabled = true;
				toolStripButton7->Enabled = true;
				toolStripButton8->Enabled = true;
				comboBox1->Enabled = true;
				toolStripButton9->Enabled = true;
				toolStripButton10->Enabled = true;
				toolStripButton11->Enabled = true;
				toolStripButton12->Enabled = true;
				toolStripButton13->Enabled = true;
				toolStripButton14->Enabled = true;
				toolStripButton15->Enabled = true;
				toolStripButton16->Enabled = true;
				toolStripButton17->Enabled = true;

				for (int i = 0; i < 256; i++)
					his[i] = 0;

}
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			if (myPixelFormat== PixelFormat::Format24bppRgb){
				for (int i = 0; i < imH; i++)
					delete [] arrayB[i];
					delete [] arrayB;
				for (int i = 0; i < imH; i++)
					delete [] arrayG[i];
					delete [] arrayG;
				for (int i = 0; i < imH; i++)
					delete [] arrayR[i];
					delete [] arrayR;
				
				}//if
				else if(myPixelFormat== PixelFormat::Format8bppIndexed){ 
					for (int i = 0; i < imH; i++)
					delete [] arrayGray[i];
					delete [] arrayGray;
				}
					Application::Exit();

}
private: System::Void invrseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Rectangle rect = Rectangle(0, 0, myBitmap->Width, myBitmap->Height);
			 BitmapData^ bmpData = myBitmap->LockBits(rect,ImageLockMode::ReadWrite, myBitmap->PixelFormat);
			 int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			 unsigned char* p = (unsigned char*)bmpData->Scan0.ToPointer();
			 int index = 0;

			 if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed){
				 for (int y = 0; y < myBitmap->Height; y++){
					 for (int x = 0; x < myBitmap->Width; x++){
						 p[index++] = 255 - arrayGray[x][y];
					 } //for x
					// index += ByteOfSkip; // 跳過剩下的 Padding bytes
				 } //for y
				
			 }else{
				 for (int y = 0; y < myBitmap->Height; y++){
					 for (int x = 0; x < myBitmap->Width; x++){
						 p[index + 0] = 255 - arrayB[x][y];
						 p[index + 1] = 255 - arrayG[x][y];
						 p[index + 2] = 255 - arrayR[x][y];
						 index += 3;
					 } //for x
					 index += ByteOfSkip; // 跳過剩下的 Padding bytes
				 } //for y
			 }
			 // Unlock the bits.
			 myBitmap->UnlockBits(bmpData);
			 
			
			 pictureBox3->Image = myBitmap;
		 }
private: System::Void grayToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Rectangle rect = Rectangle(0, 0, myBitmap->Width, myBitmap->Height);
			 BitmapData^ bmpData = myBitmap->LockBits(rect,ImageLockMode::ReadWrite, myBitmap->PixelFormat);
			 int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			 unsigned char* p = (unsigned char*)bmpData->Scan0.ToPointer();
			 int index = 0;
			 int W = myBitmap->Width;
			 int H = myBitmap->Height;

			 //create a new Grayscale Palette
				Bitmap^ myBitmap2 = gcnew Bitmap(imW, imH, PixelFormat::Format8bppIndexed);
				//setup Grayscale Palette
				ColorPalette^ grayP = myBitmap2->Palette;
				for (int i = 0; i < 256; i++)
				grayP->Entries[i] = Color::FromArgb(255, i, i, i);
				myBitmap2->Palette = grayP;
			
				this->toolStripButton3->Enabled = true;

				 for (int i = 0; i<W; i++) {
					 for (int j = 0; j<H; j++) {
						 //Color newColor = Color::FromArgb(arrayGray[i][j], arrayGray[i][j], arrayGray[i][j]);
						 //myBitmap->SetPixel(i, j, newColor);
						 p[index++] = arrayGray[j][i];

					 }
					 index += ByteOfSkip;
				 }
			 myBitmap->UnlockBits(bmpData);
			 pictureBox3->Image = myBitmap;
		 }
private: System::Void toolStripButton1_Click(System::Object^  sender, System::EventArgs^  e) {
			 openToolStripMenuItem_Click( sender,   e);
		 }
private: System::Void toolStripButton2_Click(System::Object^  sender, System::EventArgs^  e) {
			 invrseToolStripMenuItem_Click( sender, e);
		 }
private: System::Void toolStripButton3_Click(System::Object^  sender, System::EventArgs^  e) {
			 grayToolStripMenuItem_Click( sender,  e);
		 }
private: System::Void toolStripButton5_Click(System::Object^  sender, System::EventArgs^  e) {
			  exitToolStripMenuItem_Click( sender,   e);
		 }
private: System::Void undoToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 pictureBox3->Image =  pictureBox1->Image;
		 }
private: System::Void saveAsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			  saveFileDialog1->Filter = "Bitmap Image|*.bmp|AllFiles|*.*";
			 if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && saveFileDialog1->FileName->Length > 0) {
				 pictureBox3->ImageLocation = saveFileDialog1->FileName;
			 }
			 else {
				 // open image error
			 }//else
			 
			 pictureBox3->Image->Save(saveFileDialog1->FileName);
		 }
private: System::Void toolStripButton6_Click(System::Object^  sender, System::EventArgs^  e) {
			 undoToolStripMenuItem_Click( sender, e);
		 }
private: System::Void toolStripButton4_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveAsToolStripMenuItem_Click(sender,   e);
		 }
private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 histogramToolStripMenuItem_Click(sender,  e);
		 }
private: System::Void histogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
				 Bitmap^ myBitmap2 = gcnew Bitmap(256, 256, PixelFormat::Format24bppRgb);
				 pictureBox2->Image = myBitmap2;
				 Graphics^ g = Graphics::FromImage(pictureBox2->Image);
				 //red pen
				 Pen^ rPen = gcnew Pen(Color::Red,1);
				 //white fill
				 Brush^ bshWt= gcnew SolidBrush(Color::White);
				 g->FillRectangle(bshWt, 0, 0, 256, 256);
				 //Draw edges
				 Pen^ blackPen = gcnew Pen(Color::Black, 1);
				 // Draw line to screen.
				 g->DrawLine(blackPen, 0, 255, 255, 255);
				 g->DrawLine(blackPen, 0, 0, 0, 255);

				 int W = myBitmap->Width;
				 int H = myBitmap->Height;
				 int sum = 0;
				//for(int i = 0;i < 256; i++)
					//his[i] = 0;
		
				//color
				for (int i = 0; i < W; i++) {
					 for (int j = 0; j < H; j++) {
						 switch (comboBox1->SelectedIndex){
						 case 3:	 his[arrayGray[i][j]] ++ ; break;
						 case 0:	 
							 if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed)
								 his[arrayGray[i][j]] ++;
							 else his[arrayR[i][j]] ++ ;
							 break;
						 case 1:	
							 if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed)
								 his[arrayGray[i][j]] ++;
							 else his[arrayG[i][j]] ++ ; break;
						 case 2:	
							 if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed)
								 his[arrayGray[i][j]] ++;
							 else his[arrayB[i][j]] ++ ; break;
							 default:  his[i] += arrayR[i][j];
						 }
					 }
				 }

				 //count max H pixel
				 for (int i = 0; i < 256; ++i){
					 if (his[i] > sum){
						 sum = his[i];
					 }
				 }
				 label4->Text = Convert::ToString(sum);
				 label6->Text = "255";
				 label5->Text ="0";
				if (sum < 256){
					for (int i = 0;i <256; i++) {
						g->DrawLine(rPen, i, (255 - his[i]), i, 255);
					 }
				}else{
					for (int i = 0;i <256; i++) {
						g->DrawLine(rPen, i, 255 - (his[i]*255.0/sum), i, 255);
					}
				}
				if(checkBox1->Checked)
					 g->DrawLine(blackPen, T, 255, T, 0);

		 }
private: System::Void toolStripButton7_Click(System::Object^  sender, System::EventArgs^  e) {
			 histogramToolStripMenuItem_Click( sender,e);
		 }
private: System::Void toolStripButton8_Click(System::Object^  sender, System::EventArgs^  e) {
			equlizeToolStripMenuItem_Click(sender,  e);
		 }
private: System::Void equlizeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Bitmap^ myBitmap2 = gcnew Bitmap(256, 256, PixelFormat::Format24bppRgb);
			pictureBox2->Image = myBitmap2;
			Graphics^ g = Graphics::FromImage(pictureBox2->Image);

			Rectangle rect = Rectangle(0, 0, myBitmap->Width, myBitmap->Height);
			 System::Drawing::Imaging::BitmapData^ bmpData = myBitmap->LockBits(rect,
			System::Drawing::Imaging::ImageLockMode::ReadWrite, myBitmap->PixelFormat);
			 int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			 unsigned char* p = (unsigned char*)bmpData->Scan0.ToPointer();
			 int index = 0;
				 
				 //red pen
				 Pen^ rPen = gcnew Pen(Color::Red,1);
				 //white fill
				 Brush^ bshWt= gcnew SolidBrush(Color::White);
				 g->FillRectangle(bshWt, 0, 0, 256, 256);
				 Pen^ blackPen = gcnew Pen(Color::Black, 1);
				 // Draw line to screen.
				 g->DrawLine(blackPen, 0, 255, 255, 255);
				 g->DrawLine(blackPen, 0, 0, 0, 255);
				 //int sum = 0;
				  int et[256] = {0};
				  float F[256]= {0};
				  int al[256] = {0};
				  float P[256] = {0};
				  int sum = 0;
			
			for (int i = 1; i < 256; i++){
				 P[i] = (his[i]*1.0)/((imH*imW)*1.0);
				if(P[0] != 0){
					P[0] = F[0];
				}
				F[i] = F[i-1] + P[i];
				al[i] = Convert::ToInt32(F[i] * 255);
			}

			for (int i = 0; i < imW; i++) {
				for (int j = 0; j < imH; j++) {
					arrayGray[j][i] = al[arrayGray[j][i]];
					p[index++] = arrayGray[j][i];
				}
			}

			for (int i = 0; i < imW; i++) {
				for (int j = 0; j < imH; j++) {
					et[arrayGray[j][i]] ++ ;
				}
			}

			for (int i = 0; i < 256; ++i){
				if (et[i] > sum){
					sum = et[i];
				 }
			}

			if (sum < 256){
				for (int i = 0;i <256; i++) {
					g->DrawLine(rPen, i, (255 - et[i]), i, 255);
				}
			}else{
				for (int i = 0;i <256; i++) {
					g->DrawLine(rPen, i, 255 - (et[i]*256/sum), i, 255);
				}
			}

		  myBitmap->UnlockBits(bmpData);
		  pictureBox3->Image = myBitmap;
	}

private: System::Void radioButton1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void maskToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 double Mean_Filter3[3*3] = {1.0/9, 1.0/9, 1.0/9,
										1.0/9, 1.0/9, 1.0/9,
										1.0/9, 1.0/9, 1.0/9 };
			double Mean_Filter5[5*5] = {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25,
										1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25,
										1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25,
										1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25,
										1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25 };
			double Mean_Filter7[7*7] = { 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49,
										1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49,1.0/49, 1.0/49 };
			 
			double Mean_Filter9[9*9] = { 1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81,
										1.0/81, 1.0/81, 1.0/81, 1.0/81, 1.0/81,1.0/81, 1.0/81,1.0/81, 1.0/81};			 
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

				int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
				unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
				int index=0;
			 
			 
			 double* Mean_Filter;
			 double result_R=0.0 ;
			 double result_G=0.0 ;
			 double result_B=0.0 ;
			 double count = 0.0 ;
				if (radioButton1->Checked){
					MaskSize = 3;
					Mean_Filter = &Mean_Filter3[0]; //Mean_Filter = Mean_Filter;
				}//if
					else if (radioButton2->Checked){
					MaskSize = 5;
					Mean_Filter = &Mean_Filter5[0];
				}//else if
					else if (radioButton3->Checked){
					MaskSize = 7;
					Mean_Filter = &Mean_Filter7[0];
				}//else if
				else {
					MaskSize = 9;
					Mean_Filter = &Mean_Filter9[0];
				}//count = 0.0; result_R = 0.0; result_G = 0.0; result_B = 0.0;
				int c = (MaskSize-1) / 2;
				for(int j = 0; j < imH; j++ ){
					for(int i = 0; i < imW; i++ ){
						count = 0.0; 
						result_R = 0.0;
						result_G = 0.0;
						result_B = 0.0;

						for (int m = 0; m < MaskSize; m++) {
							for (int n = 0; n < MaskSize; n++) {
								if ((j-c+m>=0)&&(i-c+n>=0)&&(j-c+m<imH)&&(i-c+n<imW)) {
									result_R += (double)arrayR[i - c + n][j - c + m] * Mean_Filter[m*MaskSize + n];
									result_G += (double)arrayG[i - c + n][j - c + m] * Mean_Filter[m*MaskSize + n];
									result_B += (double)arrayB[i - c + n][j - c + m] * Mean_Filter[m*MaskSize + n];
									count += Mean_Filter[m*MaskSize + n];
								}//if
							}//for n
						}//for m

						p[index+2]= (int)(result_R/count);
						p[index+1]= (int)(result_G/count);
						p[index+0]= (int)(result_B/count);
						index += 3;
             		}//for i
					index += ByteOfSkip;
 		 		}//for j

				myBitmap->UnlockBits( bmpData ); 
				pictureBox3->Image = myBitmap;

		 }
private: System::Void noiseToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;
			 srand((unsigned)time(NULL));
			 int W = myBitmap->Width;
			 int H = myBitmap->Height;
			 double peper = Convert::ToDouble(textBox1->Text);
			 for (int i = 0; i < W; i ++) {
					for (int j = 0; j < H; j ++) {
						 double ju =  1+ rand() % 100;//point better /32767
						 if(ju <= peper/2){
							p[index + 0] = 0;
							p[index + 1] = 0;
							p[index + 2] = 0;
						 }else if(ju > peper/2 && ju <= peper){
							p[index + 0] = 255;
							p[index + 1] = 255;
							p[index + 2] = 255;
						 }else{
							 //do nothing
						 }
						 index += 3;
					 }
					index += ByteOfSkip; 
			 }


			 myBitmap->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap;
			 
		 }
private: System::Void toolStripButton9_Click(System::Object^  sender, System::EventArgs^  e) {
			 noiseToolStripMenuItem_Click(sender,   e);
		 }
private: System::Void toolStripButton10_Click(System::Object^  sender, System::EventArgs^  e) {
			 maskToolStripMenuItem_Click(sender, e);
		 }
private: System::Void toolStripButton11_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;
			 
			 

			 int s = 0;
			 int Mean_Filter3[3*3];
			 int Mean_Filter5[5*5];
			 int Mean_Filter7[7*7];
			 int Mean_Filter9[9*9];
			 int* Mean_Filter;
			 double count = 0.0 ;
			 int tmp1= 0;
			 int tmp2 = 0;
			 
			 if (radioButton1->Checked){
					MaskSize = 3;
					Mean_Filter = &Mean_Filter3[0]; //Mean_Filter = Mean_Filter;
				}//if
					else if (radioButton2->Checked){
					MaskSize = 5;
					Mean_Filter = &Mean_Filter5[0];
				}//else if
					else if (radioButton3->Checked){
					MaskSize = 7;
					Mean_Filter = &Mean_Filter7[0];
				}//else if
				else {
					MaskSize = 9;
					Mean_Filter = &Mean_Filter9[0];
				}

				
				int c = (MaskSize-1) / 2;

				//sort[MaskSize*MaskSize] = new int[MaskSize*MaskSize];
				//bigger[(imH+1)*(imW+1)] = new int[(imH+1)*(imW+1)];

				 for(int i = 0;i < imH;i++){
					 for(int j = 0;j < imW;j++){
						 s=0;
						for (int m = 0; m < MaskSize; m++) {
							for (int n = 0; n < MaskSize; n++) {	
								int l = i-c+n;int d = j-c+m;
							 if(l < 0){
								l = 0;
							 }
							 if(l> imW-1){
								l = imW-1;
							 }
							  if( d< 0){
								d = 0;
							 }
							 if( d> imH-1){
								d = imH-1;
							 }
							 
								Mean_Filter[s] = arrayGray[d][l];
								s++;
							}//for n
						}//for m


						for (int x = MaskSize*MaskSize - 1; x > 0; --x){
								bool swapped = false;
								for (int y = 0; y < x; ++y)
									if (Mean_Filter[y] > Mean_Filter[y + 1]){
										int tmp = Mean_Filter[y];
										Mean_Filter[y] = Mean_Filter[y+1];
										Mean_Filter[y+1] = tmp;
										swapped = true;
								}
								if (!swapped)
									break;
							}
						for (int m = 0; m < MaskSize; m++) {
							for (int n = 0; n < MaskSize; n++) {	
								int l = i-c+n;int d = j-c+m;
									 if(l < 0){
										l = 0;
									 }
									 if(l> imW-1){
										l = imW-1;
									 }
									  if( d< 0){
										d = 0;
									 }
									 if( d> imH-1){
										d = imH-1;
									 }
								if(arrayGray[d][l] == Mean_Filter[MaskSize*MaskSize/2]){
									tmp1 = d;
									tmp2 = l;
								}
							}
						}
								p[index + 0] = arrayB[tmp1][tmp2];
								p[index + 1] = arrayG[tmp1][tmp2];
								p[index + 2] = arrayR[tmp1][tmp2];
						index += 3;
						}
						index += ByteOfSkip; 
					} 		
				myBitmap->UnlockBits( bmpData ); 
				pictureBox3->Image = myBitmap;


	}
private: System::Void binarizationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			 BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;
			 for(int j = 0; j < imH; j++ ){
				for(int i = 0; i < imW; i++ ){
					if(arrayGray[i][j] > T){
						arrayGray[i][j] = 255;
						p[index + 0] = 255;
						p[index + 1] = 255;
						p[index + 2] = 255;
					}else{
						arrayGray[i][j] = 0;
						p[index + 0] = 0;
						p[index + 1] = 0;
						p[index + 2] = 0;
					}
					index += 3;
				}
				index += ByteOfSkip; // 跳過剩下的 Padding bytes
			 }

			 myBitmap->UnlockBits( bmpData ); 
			pictureBox3->Image = myBitmap;
			comboBox1->SelectedIndex = 3;
			histogramToolStripMenuItem_Click(  sender,  e);

		 }
private: System::Void hScrollBar1_Scroll(System::Object^  sender, System::Windows::Forms::ScrollEventArgs^  e) {
			T = hScrollBar1->Value;
			label8 -> Text = "threshold:" + Convert::ToString(T);
		 }
private: System::Void toolStripButton12_Click(System::Object^  sender, System::EventArgs^  e) {
			 binarizationToolStripMenuItem_Click(sender,e);
		 }
private: System::Void otsuToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
			
			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			 double pi[256] = {0.0};
			 double mk= 0.0;
			 double wk = 0.0;
			 double ut = 0.0;
			 double uk = 0.0;
			 double max = 0.0;
			 int sav = 0;

			 for(int i = 0;i < 256;i++){
				pi[i] =( his[i]*1.0)/((imW*imH)*1.0);
			 }

			 for(int i = 0;i < 256;i++){
				ut += i*pi[i];
				uk += pi[i];
			 }
			 
			 for(int i = 0;i < 256;i++){
				
				mk += pi[i]*i;	
				wk += pi[i];
			  
				if(max < (ut*wk - mk)*(ut*wk - mk)/(wk*(1 - wk))){
					sav = i;
					max = (ut*wk - mk)*(ut*wk - mk)/(wk*(1 - wk));
					
				}
				  
			 }

			 T = sav;
			//binarizationToolStripMenuItem_Click( sender,  e);
			 
			 for(int j = 0; j < imH; j++ ){
				for(int i = 0; i < imW; i++ ){
					if(arrayGray[i][j] >= T){
						//arrayGray[i][j] = 255;
						p[index + 0] = 255;
						p[index + 1] = 255;
						p[index + 2] = 255;
					}else{
						//arrayGray[i][j] = 0;
						p[index + 0] = 0;
						p[index + 1] = 0;
						p[index + 2] = 0;
					}
					index += 3;
				}
				index += ByteOfSkip; // 跳過剩下的 Padding bytes
			 }

			 myBitmap->UnlockBits( bmpData ); 
			pictureBox3->Image = myBitmap;
			  label8 -> Text = "threshold:" + Convert::ToString(T);
			  comboBox1->SelectedIndex = 3;
			histogramToolStripMenuItem_Click(  sender,  e);
			
		 }
private: System::Void toolStripButton13_Click(System::Object^  sender, System::EventArgs^  e) {
			 otsuToolStripMenuItem_Click( sender,  e);
		 }
private: System::Void sobToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Bitmap^ myBitmap2 = gcnew Bitmap(pictureBox1->ImageLocation);
			 Rectangle rect = Rectangle(0,0,imW,imH);
			 Rectangle rect2 = Rectangle(0,0,imW,imH);
			 BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			 myBitmap->PixelFormat );
			 BitmapData^ bmpData2 = myBitmap2->LockBits( rect2, ImageLockMode::ReadWrite,
			 myBitmap2->PixelFormat );
			
			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			int ByteOfSkip2 = bmpData2->Stride - bmpData2->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			unsigned char* p2 = (unsigned char*) bmpData2->Scan0.ToPointer();
			int index=0;
			int index2=0;
			 //Graphics^ G = Graphics::FromImage(pictureBox2->Image);
			//T = 128;
			 double **m3x3;
			 double **z;
			 double gx,gy,gx1,gy1,r,g,b,m,max = 0;
			 double min = 1000000000;
			 T = hScrollBar1->Value;
			 m3x3 = new double*[imH];
			 z = new double*[imH];
			 for(int i = 0;i < imH;i++){
				m3x3[i] = new double[imW];
				z[i] = new double[imW];
			 }
			 for(int i = 0;i < imH;i++){
				 for(int j = 0;j < imW;j++){
					z[i][j] = (arrayB[i][j]+arrayG[i][j]+arrayR[i][j])/3;
				 }
			 }
			 for(int i = 0;i < imH;i++){
				 for(int j = 0;j < imW;j++){
					int l = i-1;int r = i+1;int u = j+1;int d = j-1;
						 if(l < 0){
							l = l+1;
						 }
						 if(r > imW-1){
							r = r-1;
						 }
						 if(d < 0){
							d = d+1;
						 }
						 if( u > imH-1){
							u = u-1;
						 }
					gx = (z[u][r] + 2*z[j][r] + z[d][r]) - (z[u][l] + 2*z[j][l] + z[d][l]);
					gy = (z[d][l] + 2*z[d][i] + z[d][r]) - (z[u][l] + 2*z[u][i] + z[u][r]);
					m3x3[i][j] = sqrt(gx*gx + gy*gy);
					if(m3x3[i][j] > max)
						max = m3x3[i][j];
					if( m3x3[i][j] < min)
						min = m3x3[i][j];
				 }
			 }
			
			  for(int i = 0;i < imH;i++){
				 for(int j = 0;j < imW;j++){ 
						//m3x3 - max?m3x3-min?
						m3x3[i][j] = (m3x3[i][j]-min)*255/(max-min);
						p2[index2 + 0] = m3x3[i][j];
						p2[index2 + 1] = m3x3[i][j];
						p2[index2 + 2] = m3x3[i][j];
					if(m3x3[i][j] > T){
						p[index + 0] = 0;
						p[index + 1] = 0;
						p[index + 2] = 0;
					}else{
						p[index + 0] = 255;
						p[index + 1] = 255;
						p[index + 2] = 255;
					}
					

					index += 3;
					index2 += 3;
				 }
				 index += ByteOfSkip;
				 index2 += ByteOfSkip2;
			 }
			  myBitmap->UnlockBits( bmpData ); 
			  pictureBox3->Image = myBitmap;
			  myBitmap2->UnlockBits( bmpData2 ); 
			  pictureBox2->Image = myBitmap2;

			  for (int i = 0; i < imH; i++)
				 delete[] m3x3[i];
			delete[] m3x3;
			for (int i = 0; i < imH; i++)
				 delete[] z[i];
			delete[] z;
		 }
private: System::Void toolStripButton14_Click(System::Object^  sender, System::EventArgs^  e) {
			 sobToolStripMenuItem_Click(  sender,   e);
		 }
private: System::Void thinningToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
			
			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;
			 
			 int t = 0;
			 int b1,b2,b3,b4,b5,b6,b7,b8,b9 = 0;
			 int n = 0;
			 
			 bool flag = true;
			 int **delet_part = new int*[imH];
			 for (int i = 0; i < imH; i++)
				 delet_part[i] = new int[imW];
			

			for (int i = 0;i < imW;i++)arrayGray[i][0] = 255;
			for (int i = 0;i < imW;i++)arrayGray[i][imH - 1] = 255;
			for (int j = 0;j < imH;j++)arrayGray[0][j] = 255;
			for (int j = 0;j < imH;j++)arrayGray[imW - 1][j] = 255;

			while(flag){
				flag = false;
				for (int i = 1;i < imH-1;i++){
					 for(int j = 1;j < imW-1;j++){
						 delet_part[i][j] = arrayGray[i][j];
						if((b9 = binary(arrayGray[i][j])) == 1){
							b1 = binary(arrayGray[i-1][j-1]);
							b2 = binary(arrayGray[i][j-1]);
							b3 = binary(arrayGray[i+1][j-1]);
							b4 = binary(arrayGray[i+1][j]);
							b5 = binary(arrayGray[i+1][j+1]);
							b6 = binary(arrayGray[i][j+1]);
							b7 = binary(arrayGray[i-1][j+1]);
							b8 = binary(arrayGray[i-1][j]);
				
								if(b1 == 1 && b2 == 0)t++;
								if(b2 == 1 && b3 == 0)t++;
								if(b3 == 1 && b4 == 0)t++;
								if(b4 == 1 && b5 == 0)t++;
								if(b5 == 1 && b6 == 0)t++;
								if(b6 == 1 && b7 == 0)t++;
								if(b7 == 1 && b8 == 0)t++;
								if(b8 == 1 && b1 == 0)t++;
								n = b1+b2+b3+b4+b5+b6+b7+b8;
								if((b2*b4*b6) == 0 && n >=2 && n <=6 && (b6*b8*b4) == 0 && t == 1){
									delet_part[i][j] = 255;
									flag == true;
								}//if 
								t = 0;
						}//if
					}//for j
				}//for i
	
			for (int i = 1;i < imH-1;i++){
				for(int j = 1;j < imW-1;j++){
					arrayGray[i][j] = delet_part[i][j];
				}
			}
			
			for (int i = 1;i < imH-1;i++){
				 for(int j = 1;j < imW-1;j++){
					 if((b9 = binary(arrayGray[i][j])) == 1){
					b1 = binary(arrayGray[i-1][j-1]);
					b2 = binary(arrayGray[i][j-1]);
					b3 = binary(arrayGray[i+1][j-1]);
					b4 = binary(arrayGray[i+1][j]);
					b5 = binary(arrayGray[i+1][j+1]);
					b6 = binary(arrayGray[i][j+1]);
					b7 = binary(arrayGray[i-1][j+1]);
					b8 = binary(arrayGray[i-1][j]);
					

						if(b1 == 1 && b2 == 0)t++;
						if(b2 == 1 && b3 == 0)t++;
						if(b3 == 1 && b4 == 0)t++;
						if(b4 == 1 && b5 == 0)t++;
						if(b5 == 1 && b6 == 0)t++;
						if(b6 == 1 && b7 == 0)t++;
						if(b7 == 1 && b8 == 0)t++;
						if(b8 == 1 && b1 == 0)t++;
						n = b1+b2+b3+b4+b5+b6+b7+b8;
						if((b2*b4*b8) == 0 && n >=2 && n <=6 &&( b2*b6*b8) == 0 && t == 1){
							delet_part[i][j] = 255;
							flag = true;
						}//if
						t = 0;
					 }//if
					}//for j
				 }//for i

				for (int i = 1;i < imH-1;i++){
					for(int j = 1;j < imW-1;j++){
						arrayGray[i][j] = delet_part[i][j];
					}//for i
				}//for j
			}//while

			for (int y = 0; y < imH; y++){
				for (int x = 0; x < imW; x++){
					 p[index++] = arrayGray[x][y];
				} //for x
			} //for y
			for (int i = 0; i < imH; i++)
				 delete[] delet_part[i];
			delete[] delet_part;
			 myBitmap->UnlockBits( bmpData ); 
			  pictureBox3->Image = myBitmap;

		 }
private: System::Void toolStripButton15_Click(System::Object^  sender, System::EventArgs^  e) {
			 thinningToolStripMenuItem_Click(sender, e);
		 }
private: System::Void dFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			COMPLEX1 **dgray;
			int ** r;
			double xl = 0.0;
			double tmp = 0.0;
			double l = 0.0;
			double c = Convert::ToDouble(textBox2->Text);
			dgray = new COMPLEX1*[imH];
			for(int j = 0;j < imH;j++){
				dgray[j] = new COMPLEX1[imW];	
			}//for j

			r = new int*[imH];
			for(int j = 0;j < imH;j++){
				r[j] = new int[imW];	
			}//for j

			for(int i = 0;i < imH;i++){
				for(int j = 0;j < imW;j++){
					r[i][j] = 0;
				}
			}

			for(int i = 0;i < imH;i++){
				for(int j = 0;j < imW;j++){
					dgray[i][j].real = (double)signal(i+j)*arrayGray[i][j];
					dgray[i][j].imag = 0.0;
				}
			}
			DFT2d(dgray,imH,1);

			for(int i = 0;i < imH;i++){
				for(int j = 0;j < imW;j++){

					tmp =sqrt(dgray[i][j].real*dgray[i][j].real + dgray[i][j].imag*dgray[i][j].imag);
					l = (double)log(tmp + 1.0);
					r[i][j] =(int)c *l;
					if(r[i][j] > xl)
						xl = r[i][j];
				}
			}

			for(int i = 0;i < imH;i++){
				for(int j = 0;j < imW;j++){
					p[index] = r[j][i]*255.0/(xl*1.0);
					index++;
				}
			}
				
			myBitmap->UnlockBits( bmpData ); 
			 pictureBox2->Image = myBitmap;
		 }
private: System::Void toolStripButton16_Click(System::Object^  sender, System::EventArgs^  e) {
			 dFTToolStripMenuItem_Click(sender,e);
		 }
private: System::Void fFTToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			
		 }
private: System::Void toolStripButton17_Click(System::Object^  sender, System::EventArgs^  e) {
			 fFTToolStripMenuItem_Click(sender,  e) ;
		 }
private: System::Void frecrencyFilteringToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			COMPLEX1 **dgray;
			double max = 0.0;
			double **D;
			COMPLEX1 **H;
			double d0 = Convert::ToDouble(textBox3->Text);
			int n = Convert::ToInt32(textBox4->Text);
			
			dgray = new COMPLEX1*[imH];
			for(int j = 0;j < imH;j++){
				dgray[j] = new COMPLEX1[imW];	
			}//for j

			D = new double*[imH];
			for(int j = 0;j < imH;j++){
				D[j] = new double[imW];	
			}//for j

			H = new COMPLEX1*[imH];
			for(int j = 0;j < imH;j++){
				H[j] = new COMPLEX1[imW];	
			}//for j

			for(int i = 0;i < imW;i++){
				for(int j = 0;j < imH;j++){
					dgray[i][j].real = (double)signal(i+j)*arrayGray[i][j];
					dgray[i][j].imag = 0.0;
				}
			}
			DFT2d(dgray,imH,1);
			for(int u = 0;u < imW;u++){
				for(int v = 0;v < imH;v++){
					D[u][v] = sqrt(pow(u - imW*1.0/2.0, 2) + pow(v - imH*1.0/2.0,2));				
				}
			}
			if(radioButton5->Checked){
				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						H[u][v].imag = 0;
						if(D[u][v] <= d0){
							H[u][v].real = 1.0;
							H[u][v].imag = 1.0;
						}else{
							H[u][v].real = 0.0;
							H[u][v].imag = 0.0;
						}

						H[u][v].real *= dgray[u][v].real;
						H[u][v].imag *= dgray[u][v].imag;
					}
				}
			}

			if(radioButton6->Checked){
				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						H[u][v].real = 1.0/(1.0+pow(D[u][v]/d0,2*n));
						H[u][v].imag = 1.0/(1.0+pow(D[u][v]/d0,2*n));
					
						H[u][v].real *= dgray[u][v].real;
						H[u][v].imag *= dgray[u][v].imag;
					}
				}
			}

			DFT2d(H,imH,-1);

			/*for(int u = 0;u < imW;u++){
				for(int v = 0;v < imH;v++){
					if(H[u][v].real > max)
						max = H[u][v].real;
				}
			}*/

			if(checkBox2->Checked){
				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						if(H[v][u].real < 0.0)
							H[v][u].real *= -1.0;
						p[index] = H[v][u].real;
						index++;
					}
				}
			}else{

				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						p[index] = (unsigned char)((double)signal(u+v)*H[v][u].real);
						index++;			
					}
				}
			}

			
			//dFTToolStripMenuItem_Click( sender,e);

			myBitmap->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap;

			 for (int i = 0; i < imH; i++){
				 delete[] D[i];
				 delete[] H[i];
			 }
			delete[] D;
			delete[] H;

		 }
private: System::Void toolStripButton18_Click(System::Object^  sender, System::EventArgs^  e) {
			 hFToolStripMenuItem_Click(sender,e);
		 }

private: System::Void toolStripButton19_Click(System::Object^  sender, System::EventArgs^  e) {
			 frecrencyFilteringToolStripMenuItem_Click(sender,e);
		 }
private: System::Void hFToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Rectangle rect = Rectangle(0,0,imW,imH);
			BitmapData^ bmpData = myBitmap->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

			int ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			COMPLEX1 **dgray;
			double max = 0.0;
			double **D;
			COMPLEX1 **H;
			double d0 = Convert::ToDouble(textBox3->Text);
			int n = Convert::ToInt32(textBox4->Text);
			dgray = new COMPLEX1*[imH];
			for(int j = 0;j < imH;j++){
				dgray[j] = new COMPLEX1[imW];	
			}//for j

			D = new double*[imH];
			for(int j = 0;j < imH;j++){
				D[j] = new double[imW];	
			}//for j

			H = new COMPLEX1*[imH];
			for(int j = 0;j < imH;j++){
				H[j] = new COMPLEX1[imW];	
			}//for j

			for(int i = 0;i < imW;i++){
				for(int j = 0;j < imH;j++){
					dgray[i][j].real = (double)signal(i+j)*arrayGray[i][j];
					dgray[i][j].imag = 0.0;
				}
			}
			DFT2d(dgray,imH,1);
			for(int u = 0;u < imW;u++){
				for(int v = 0;v < imH;v++){
					D[u][v] = sqrt(pow(u - imW*1.0/2.0, 2) + pow(v - imH*1.0/2.0,2));				
				}
			}
			if(radioButton5->Checked){
				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						H[u][v].imag = 0;
						if(D[u][v] <= d0){
							H[u][v].real = 1.0;
							H[u][v].imag = 1.0;
						}else{
							H[u][v].real = 0.0;
							H[u][v].imag = 0.0;
						}

						H[u][v].real *= dgray[u][v].real;
						H[u][v].imag *= dgray[u][v].imag;
					}
				}
			}

			if(radioButton6->Checked){
				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						H[u][v].real = 1.0/(1.0+pow(d0/D[u][v],2*n));
						H[u][v].imag = 1.0/(1.0+pow(d0/D[u][v],2*n));
					
						H[u][v].real *= dgray[u][v].real;
						H[u][v].imag *= dgray[u][v].imag;
					}
				}
			}

			DFT2d(H,imH,-1);

			for(int u = 0;u < imW;u++){
				for(int v = 0;v < imH;v++){
					if(H[u][v].real > max)
						max = H[u][v].real;
				}
			}

			

				for(int u = 0;u < imW;u++){
					for(int v = 0;v < imH;v++){
						p[index] = abs(H[v][u].real)+abs(H[v][u].imag);
						index++;			
					}
				}
			

			
			//dFTToolStripMenuItem_Click( sender,e);

			myBitmap->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap;

			 for (int i = 0; i < imH; i++){
				 delete[] D[i];
				 delete[] H[i];
			 }
			delete[] D;
			delete[] H;
		 }
private: System::Void toolStripButton20_Click(System::Object^  sender, System::EventArgs^  e) {
			 double scale = Convert::ToDouble(textBox5->Text);
			 int newimW = imW * scale;
			 int newimH = imH * scale;
			 int ByteOfSkip;
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Bitmap^ myBitmap2 = gcnew Bitmap(newimW, newimH, myBitmap->PixelFormat);
			 //setup Grayscale Palette
			
			 if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed)
				myBitmap2->Palette = myBitmap->Palette;	

			Rectangle rect = Rectangle(0,0,newimW,newimH);
			BitmapData^ bmpData = myBitmap2->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
	
			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed){
				ByteOfSkip = bmpData->Stride - bmpData->Width;
			}else{
				ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			}
			
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;


			
			int si,sj ;

			if(myBitmap->PixelFormat== PixelFormat::Format8bppIndexed){
				 for(int i = 0;i < newimH;i++){
					 for(int j = 0;j < newimW;j++){ 
						si = (int)(i/scale);
						sj = (int)(j/scale);
						p[index ++] = arrayGray[sj][si];	
					 }
					 index += ByteOfSkip;
				 }
			 }else{
				  for(int i = 0;i < newimH;i++){
					 for(int j = 0;j < newimW;j++){ 
						si = (int)(i/scale);
						sj = (int)(j/scale);
						p[index + 0] = arrayB[sj][si];
						p[index + 1] = arrayG[sj][si];
						p[index + 2] = arrayR[sj][si];
						index += 3;
					 }
					 index += ByteOfSkip;
				 }
						
					}

			myBitmap2->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap2;


		 }

private: System::Void toolStripButton21_Click(System::Object^  sender, System::EventArgs^  e) {
			 double scale = Convert::ToDouble(textBox5->Text);
			 int newimW = imW * scale;
			 int newimH = imH * scale;
			 int ByteOfSkip;
			 if(scale <= 0.0)
				 scale = 2.0;
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Bitmap^ myBitmap2 = gcnew Bitmap(newimW, newimH, myBitmap->PixelFormat);
			 //setup Grayscale Palette
			
			 if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed)
				myBitmap2->Palette = myBitmap->Palette;	

			Rectangle rect = Rectangle(0,0,newimW,newimH);
			BitmapData^ bmpData = myBitmap2->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
	
			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed){
				ByteOfSkip = bmpData->Stride - bmpData->Width;
			}else{
				ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			}
			
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			int xa,ya,xb,yb;
			double u,l,f1,f2,dx,dy;
		
				for(int i = 0;i < newimH;i++){
					 for(int j = 0;j < newimW;j++){ 
						dx = (j*1.0)/scale;
						dy = (i*1.0)/scale;
						xa = (int)dx;
						ya = (int)dy;
						u = dx - xa;
						l = dy - ya;
						xb = xa +1;
						yb = ya +1;

						if(xb > imW - 1)
							xb = imW - 1;
						if(yb > imH - 1)
							yb = imH -1;

						f1 = u*arrayGray[xa][yb] + (1.0-u)*arrayGray[xa][ya];
						f2 = u*arrayGray[xb][yb] + (1.0-u)*arrayGray[xb][ya];
						p[index++] = (unsigned char)(l*f2 + (1.0-l)*f1 +0.5) ;

					 }
					  index += ByteOfSkip;
				}
			
			myBitmap2->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap2;
		 }
private: System::Void toolStripButton23_Click(System::Object^  sender, System::EventArgs^  e) {
			double pi = 4.0 * atan(1.0);
			double  rotate = Convert::ToDouble(textBox6->Text)/45.0*atan(1.0);
			int newimW = (int)(imW * 1.414 +0.5);
			int newimH = (int)(imH * 1.414 +0.5);
			int ByteOfSkip;
			Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			Bitmap^ myBitmap2 = gcnew Bitmap(newimW, newimH, myBitmap->PixelFormat);

			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed)
				myBitmap2->Palette = myBitmap->Palette;	
			Rectangle rect = Rectangle(0,0,newimW,newimH);
			BitmapData^ bmpData = myBitmap2->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );

			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed){
				ByteOfSkip = bmpData->Stride - bmpData->Width;
			}else{
				ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			}
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			int ** aR;
			aR = new int*[newimH];
			for(int j = 0;j < newimH;j++){
				aR[j] = new int[newimW];	
			}//for j
			
			int sx = (int)(newimH - imH)/2;
			int sy = (int)(newimW - imW)/2;
			int cx = (int)(newimH/2);
			int cy = (int)(newimW/2);

			int ox,oy;

			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed){
				
				for(int i = 0;i < imH;i++){
					for(int j = 0;j < imW;j++){ 
						aR[sx + i][sy + j] = arrayGray[i][j];
					}
				}

				for(int i = 0;i < newimH;i++){
					for(int j = 0;j < newimW;j++){ 
						aR[i][j] = 0;
					}
				}

				for(int i = 0;i < imH;i++){
					for(int j = 0;j < imW;j++){ 
						aR[sx + i][sy + j] = arrayGray[i][j];

					}
				}

				for(int i = 0;i < newimH;i++){
					for(int j = 0;j < newimW;j++){ 

						ox = (int)(cos(rotate)*(i-cx) + sin(rotate)*(j-cy)) +cx ;
						oy = (int)(-sin(rotate)*(i-cx) + cos(rotate)*(j-cy)) + cy;
					
						if(ox >= 0 && oy >= 0 && ox < newimH && oy < newimW){
							p[index] = aR[oy][ox];	
						}
						index++;
					}
					index += ByteOfSkip;
				}

				for (int i = 0; i < newimH; i++){
					 delete[] aR[i];
				 }
				delete[] aR;

			}else{
				int ** aG;
				aG = new int*[newimH];
				for(int j = 0;j < newimH;j++){
					aG[j] = new int[newimW];	
				}//for j
				int ** aB;
				aB = new int*[newimH];
				for(int j = 0;j < newimH;j++){
					aB[j] = new int[newimW];	
				}//for j

				for(int i = 0;i < newimH;i++){
					for(int j = 0;j < newimW;j++){ 
						aR[i][j] = 0;
						aG[i][j] = 0;
						aB[i][j] = 0;
					}
				}

				for(int i = 0;i < imH;i++){
					for(int j = 0;j < imW;j++){ 
						aR[sx + i][sy + j] = arrayR[i][j];
						aG[sx + i][sy + j] = arrayG[i][j];
						aB[sx + i][sy + j] = arrayB[i][j];

					}
				}

				for(int i = 0;i < newimH;i++){
					for(int j = 0;j < newimW;j++){ 

						ox = (int)(cos(rotate)*(i-cx) + sin(rotate)*(j-cy)) +cx ;
						oy = (int)(-sin(rotate)*(i-cx) + cos(rotate)*(j-cy)) + cy;
					

						if(ox >= 0 && oy >= 0 && ox < newimH && oy < newimW){
							p[index+0] = aB[oy][ox];
							p[index+1] = aG[oy][ox];
							p[index+2] = aR[oy][ox];
						}
						index += 3;
					}
					index += ByteOfSkip;
				}

				for (int i = 0; i < newimH; i++){
					 delete[] aR[i];
					 delete[] aG[i];
					 delete[] aB[i];
				 }
				delete[] aR;
				delete[] aG;
				delete[] aB;
			}

			myBitmap2->UnlockBits( bmpData ); 
				pictureBox3->Image = myBitmap2;
		 }
private: System::Void toolStripButton22_Click(System::Object^  sender, System::EventArgs^  e) {
			  double scale = Convert::ToDouble(textBox5->Text);
			 int newimW = imW * scale;
			 int newimH = imH * scale;
			 int ByteOfSkip;
			 if(scale <= 0.0)
				 scale = 2.0;
			 Bitmap^ myBitmap = gcnew Bitmap(pictureBox1->ImageLocation);
			 Bitmap^ myBitmap2 = gcnew Bitmap(newimW, newimH, myBitmap->PixelFormat);
			 //setup Grayscale Palette
			
			 if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed)
				myBitmap2->Palette = myBitmap->Palette;	

			Rectangle rect = Rectangle(0,0,newimW,newimH);
			BitmapData^ bmpData = myBitmap2->LockBits( rect, ImageLockMode::ReadWrite,
			myBitmap->PixelFormat );
	
			if (myBitmap2->PixelFormat == PixelFormat::Format8bppIndexed){
				ByteOfSkip = bmpData->Stride - bmpData->Width;
			}else{
				ByteOfSkip = bmpData->Stride - bmpData->Width * 3;
			}
			
			unsigned char* p = (unsigned char*) bmpData->Scan0.ToPointer();
			int index=0;

			int xa,ya,xb,yb,xc,yc,xd,yd;
			double u,l,f1,f2,dx,dy;
			double f[8] = {0};
			

				for(int i = 0;i < newimH;i++){
					 for(int j = 0;j < newimW;j++){ 
						dx = (j*1.0)/scale;
						dy = (i*1.0)/scale;
						xa = (int)dx;//|x|
						ya = (int)dy;
						u = dx - xa;//x-|x|
						l = dy - ya;
						xb = xa +1;
						yb = ya +1;
						xc = xa + 2;
						yc = ya + 2;
						xd = xa - 1;
						yd = ya - 1;

						f[0] = 1 + u;
						f[1] = u;
						f[2] = 1 - u;
						f[3] = 2 - u;
						f[4] = 1 + l;
						f[5] = l;
						f[6] = 1 - l;
						f[7] = 2 - l;

						if(xb > imW - 1)
							xb = imW - 1;
						if(yb > imH - 1)
							yb = imH -1;
						
						if(xc > imW - 1)
							xc = imW - 1;
						if(yc > imH - 1)
							yc = imH -1;
						
						if(xd < 0)
							xd = 0;
						if(yd < 0)
							yd = 0;
						
						

						for(int a = 0;a < 8;a++){
							if(abs(f[a]) < 1){
								f[a] = 1 - 2*f[a]*f[a] + abs(f[a]*f[a]*f[a]);
							}else if(abs(f[a]) >= 1 && abs(f[a]) < 2){
								f[a] = 4 -8*abs(f[a]) + 5*f[a]*f[a] - abs(f[a]*f[a]*f[a]);
							}else{
								f[a] = 0;
							}
						}

						double f1 = f[4] * arrayGray[xd][yd] + f[5] * arrayGray[xd][ya] + f[6] * arrayGray[xd][yb] + f[7] * arrayGray[xd][yc]; 
						double f2 =	f[4] * arrayGray[xa][yd] + f[5] * arrayGray[xa][ya] + f[6] * arrayGray[xa][yb] + f[7] * arrayGray[xa][yc]; 
						double f3 = f[4] * arrayGray[xb][yd] + f[5] * arrayGray[xb][ya] + f[6] * arrayGray[xb][yb] + f[7] * arrayGray[xb][yc]; 
						double f4 = f[4] * arrayGray[xc][yd] + f[5] * arrayGray[xc][ya] + f[6] * arrayGray[xc][yb] + f[7] * arrayGray[xc][yc]; 


						p[index++] = (unsigned char)abs(f1*f[0] + f2*f[1] + f3*f[2] + f4*f[3]);

					 }
					  index += ByteOfSkip;
				}
			
			myBitmap2->UnlockBits( bmpData ); 
			 pictureBox3->Image = myBitmap2;
		 }
};
}

