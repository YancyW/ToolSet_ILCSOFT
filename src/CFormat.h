#pragma once
#ifndef CFORMAT_H
#define CFORMAT_H  
#include <iostream>
#include <string> 
#include <iomanip> 
#include "TStyle.h"
#include "CPrint.h"
using ToolSet::operator<<;

namespace ToolSet{
	/**
	 * @brief ShowMessage : print out with special format, make the output looks concisely
	 *
	 * @tparam TMess1
	 * @tparam TMess2
	 * @tparam TMess3
	 * @tparam TMess4
	 * @param level
	 * @param mess
	 * @param ddata
	 * @param ddata_comm
	 * @param ddata_comm1
	 */
	template <typename TMess1, typename TMess2,typename TMess3, typename TMess4> 
		void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata, TMess3 ddata_comm, TMess4 ddata_comm1){
			std::cout.setf(std::ios::left);
			std::string fill1="";
			std::string fill2="     ";
			std::string fill3="           ";
			std::string fill4="               ";
			std::string fill5="                    ";
			std::string fill6="                         ";
			std::string fill;

			int  fillnum1=0;
			int  fillnum2=5;
			int  fillnum3=10;
			int  fillnum4=15;
			int  fillnum5=20;
			int  fillnum6=25;
			int  fillnum;

			switch(level){
				case 1:fill=fill1;fillnum=fillnum1;break;
				case 2:fill=fill2;fillnum=fillnum2;break;
				case 3:fill=fill3;fillnum=fillnum3;break;
				case 4:fill=fill4;fillnum=fillnum4;break;
				case 5:fill=fill5;fillnum=fillnum5;break;
				case 6:fill=fill6;fillnum=fillnum6;break;
				default:fill=fill1;
			}

			std::cout << fill << std::setw(65-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << "  " << ddata_comm << "  " << ddata_comm1 << std::endl;
		}

	template <typename TMess1, typename TMess2,typename TMess3> 
		void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata, TMess3 ddata_comm){
			std::cout.setf(std::ios::left);
			std::string fill1="";
			std::string fill2="     ";
			std::string fill3="           ";
			std::string fill4="               ";
			std::string fill5="                    ";
			std::string fill6="                         ";
			std::string fill;

			int  fillnum1=0;
			int  fillnum2=5;
			int  fillnum3=10;
			int  fillnum4=15;
			int  fillnum5=20;
			int  fillnum6=25;
			int  fillnum;

			switch(level){
				case 1:fill=fill1;fillnum=fillnum1;break;
				case 2:fill=fill2;fillnum=fillnum2;break;
				case 3:fill=fill3;fillnum=fillnum3;break;
				case 4:fill=fill4;fillnum=fillnum4;break;
				case 5:fill=fill5;fillnum=fillnum5;break;
				case 6:fill=fill6;fillnum=fillnum6;break;
				default:fill=fill1;
			}

			std::cout << fill << std::setw(65-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << "  " << ddata_comm << std::endl;
		}


	template <typename TMess1, typename TMess2> 
		void ShowMessage(Int_t level, TMess1 mess, TMess2 ddata){
			std::cout.setf(std::ios::left);
			std::string fill1="";
			std::string fill2="     ";
			std::string fill3="           ";
			std::string fill4="               ";
			std::string fill5="                    ";
			std::string fill6="                         ";
			std::string fill;

			int  fillnum1=0;
			int  fillnum2=5;
			int  fillnum3=10;
			int  fillnum4=15;
			int  fillnum5=20;
			int  fillnum6=25;
			int  fillnum;

			switch(level){
				case 1:fill=fill1;fillnum=fillnum1;break;
				case 2:fill=fill2;fillnum=fillnum2;break;
				case 3:fill=fill3;fillnum=fillnum3;break;
				case 4:fill=fill4;fillnum=fillnum4;break;
				case 5:fill=fill5;fillnum=fillnum5;break;
				case 6:fill=fill6;fillnum=fillnum6;break;
				default:fill=fill1;
			}

			std::cout << fill << std::setw(65-fillnum) << std::setfill(' ') << mess  << ":    " << ddata << std::endl;
		}



	template <typename TMess1> 
		void ShowMessage (Int_t level, TMess1 mess){
			std::string fill1="";
			std::string fill2="     ";
			std::string fill3="          ";
			std::string fill4="               ";
			std::string fill5="                    ";
			std::string fill6="                         ";
			std::string fill;
			std::string fillter;

			int  fillnum1=0;
			int  fillnum2=5;
			int  fillnum3=10;
			int  fillnum4=15;
			int  fillnum5=20;
			int  fillnum6=25;
			int  fillnum;

			switch(level){
				case 1:fill=fill1;fillnum=fillnum1;break;
				case 2:fill=fill2;fillnum=fillnum2;break;
				case 3:fill=fill3;fillnum=fillnum3;break;
				case 4:fill=fill4;fillnum=fillnum4;break;
				case 5:fill=fill5;fillnum=fillnum5;break;
				case 6:fill=fill6;fillnum=fillnum6;break;
				default:fill=fill1;
			}

			int fillsize= (90 - fillnum ); 
			if(fillsize%2==1){
				fillter=" *";
			}
			else{
				fillter=" ";
			}
			std::cout << fill << std::setw(fillsize) << std::setfill('*') << "" << " " << mess << fillter << std::setw(fillsize) << std::setfill('*') << "" << std::endl;
		}

	void ShowMessage (Int_t level);
	void ShowMessage ();


}
#endif
