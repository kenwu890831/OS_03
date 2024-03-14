# include<fstream>
# include<iostream>
# include<vector>
#include<algorithm>
#include <queue>
using namespace std;

struct Data{ // 取消清單
    string frameTemp ;
    bool F = false ;

};

struct weightData{ // 取消清單
    char task ;
    int weight = 0 ;

};

class  scheduling {
private:
	int numOfPageFrame ;
	int method ;
	string inputFileName ;
	vector< char > list ;
	vector< char > frame ;
	vector< weightData > frame2 ;
	vector < Data > FIFOTemp ;
	vector < Data > LRUTemp ;
	vector < Data > LFUandLRUTemp ;
	vector < Data > MFUandFIFOTemp ;
	vector < Data > MFUandLRUTemp ;
    int pageReplace[5] ;
public:


    void reset(  ) {
        list.clear();
        frame.clear();
        frame2.clear();
        FIFOTemp.clear();
        LRUTemp.clear();
        LFUandLRUTemp.clear() ;
        MFUandFIFOTemp.clear() ;
        MFUandLRUTemp.clear() ;
    }


	bool readFile() {
        int inputNum ;
        Data temp ;
        cout << endl << "Input a file number : " ;
        cin >> inputFileName ;
        char input ;
        fstream theFile;
        theFile.open( inputFileName+".txt" ); // 開啟指定檔案
        int count = 0 ;
        if ( theFile.is_open() ) { // 如果有打開檔案
            theFile >> method ;
            theFile >> numOfPageFrame ; // numOfPageFrame
            //cout << numOfPageFrame << endl ;
            while ( theFile >> input ) {
                list.push_back( input ) ;
            } // read

            if ( method == 1 ) {
                    FIFO() ;
                    write() ;
            }
            else if ( method == 2 ) {
                    LRU() ;
                    write() ;
            }
            else if ( method == 3 ) {
                    LFUandLRU() ;
                    write() ;
            }
            else if ( method == 4 ) {
                    MFUandFIFO() ;
                    write() ;
            }
            else if ( method == 5 ) {
                    MFUandLRU() ;
                    write() ;
            }
            else if ( method == 6 ) {
                    FIFO() ;
                    LRU() ;
                    LFUandLRU() ;
                    MFUandFIFO() ;
                    MFUandLRU() ;
                    write() ;
            }


            //for ( int i = 0 ; i < list.size() ; i++)
                //cout << list.at(i) << endl;
            return true ;
        } // if
        else {
            cout << inputFileName + ".txt does not exist!" << endl ;
            return false ;
        }
    } // readFile

    void FIFO () {
        pageReplace[0] = 0 ;
        Data temp ;
        frame.clear();
        for ( int i = 0 ; i < list.size() ; i++ ) {
            bool check = false ;
            string pageFrame = "";
            if ( frame.size() < numOfPageFrame) {
                for ( int k = 0 ; k < frame.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame.at(k) == list.at(i) )
                        check = true;
                } // 檢查是否已擁有
                if ( check)
                    temp.F = false ;
                else{
                    frame.push_back( list.at(i)) ;
                    temp.F = true ;
                }

                for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                }

                temp.frameTemp = pageFrame ;
                FIFOTemp.push_back( temp ) ;
            }
            else {
                for ( int k = 0 ; k < frame.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame.at(k) == list.at(i) )
                        check = true;
                }

                if ( !check ) {
                    pageReplace[0]++ ;
                    frame.erase(frame.begin()) ;
                    frame.push_back( list.at(i)) ;
                    for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = true ;
                    FIFOTemp.push_back( temp ) ;
                } // not have
                else {
                    for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = false ;
                    FIFOTemp.push_back( temp ) ;
                } // have num

            }
        } // 執行
    } //FIFO

    void LRU () {
        frame.clear();
        frame2.clear();
        pageReplace[1] = 0 ;
        Data temp ;
        int checkPlace ;
        for ( int i = 0 ; i < list.size() ; i++ ) {
            bool check = false ;
            string pageFrame = "";
            if ( frame.size() < numOfPageFrame) {
                for ( int k = 0 ; k < frame.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame.at(k) == list.at(i) ) {
                        check = true;
                        checkPlace = k ;
                    }
                } // 檢查是否已擁有
                if ( check) {
                    temp.F = false ;
                    frame.erase(frame.begin() + checkPlace) ;
                    frame.push_back( list.at(i)) ;
                }
                else{
                    frame.push_back( list.at(i)) ;
                    temp.F = true ;
                }

                for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                }

                temp.frameTemp = pageFrame ;
                LRUTemp.push_back( temp ) ;
            }
            else {
                int numPlace ;
                for ( int k = 0 ; k < frame.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame.at(k) == list.at(i) ) {
                        check = true;
                        numPlace = k ;
                    }

                }

                if ( !check ) {
                    pageReplace[1]++ ;
                    frame.erase(frame.begin()) ;
                    frame.push_back( list.at(i)) ;
                    for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = true ;
                    LRUTemp.push_back( temp ) ;
                } // not have
                else {
                    //out << numPlace << endl ;
                    frame.erase(frame.begin() + numPlace) ;
                    frame.push_back( list.at(i)) ;
                    for ( int j = (frame.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame.at(j) ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = false ;
                    LRUTemp.push_back( temp ) ;
                } // have num

            }
        } // 執行
    } // LRU

    void LFUandLRU () {
        frame.clear();
        frame2.clear();
        pageReplace[2] = 0 ;
        Data temp ;
        weightData temp2 ;
        int checkPlace ;
        for ( int i = 0 ; i < list.size() ; i++ ) {
            bool check = false ;
            string pageFrame = "";
            if ( frame2.size() < numOfPageFrame) {
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    if ( frame2.at(k).task == list.at(i) ) {
                        check = true;
                        checkPlace = k ;
                    }

                } // 檢查是否已擁有
                if ( check) {
                    temp.F = false ;
                    temp2.task = list.at(i) ;
                    temp2.weight = frame2.at(checkPlace).weight +1 ;
                    frame2.erase(frame2.begin() + checkPlace) ;
                    frame2.push_back( temp2) ;
                }
                else{
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    frame2.push_back(temp2) ;
                    temp.F = true ;
                }

                for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                }

                temp.frameTemp = pageFrame ;
                LFUandLRUTemp.push_back( temp ) ;
            }
            else {
                int numPlace ;
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame2.at(k).task == list.at(i) ) {
                        check = true;
                        numPlace = k ;
                    }

                }

                if ( !check ) {
                    pageReplace[2]++ ;
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    int eraserNum = frame2.at(0).weight;
                    int eraserPlace = 0 ;
                    for ( int q = 0 ;  q < frame2.size() ; q++ ) {
                        if ( frame2.at(q).weight < frame2.at(eraserPlace).weight) {
                            eraserNum =  frame2.at(q).weight ;
                            eraserPlace = q ;
                        }

                    }
                    frame2.erase(frame2.begin() + eraserPlace) ;
                    frame2.push_back( temp2) ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = true ;
                    LFUandLRUTemp.push_back( temp ) ;
                } // not have
                else {

                    temp2.task =frame2.at(numPlace).task ;
                    temp2.weight =frame2.at(numPlace).weight ;
                    temp2.weight ++ ;
                    frame2.erase(frame2.begin() + numPlace) ;
                    frame2.push_back( temp2) ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = false ;
                    LFUandLRUTemp.push_back( temp ) ;
                } // have num

            }
        } // 執行
    } // LFUandLRU

    void MFUandFIFO () {
        frame.clear();
        frame2.clear();
        pageReplace[3] = 0 ;
        Data temp ;
        weightData temp2 ;
        for ( int i = 0 ; i < list.size() ; i++ ) {
            bool check = false ;
            string pageFrame = "";
            if ( frame2.size() < numOfPageFrame) {
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    if ( frame2.at(k).task == list.at(i) ){
                        check = true;
                        frame2.at(k).weight++ ;
                    }

                } // 檢查是否已擁有
                if ( check)
                    temp.F = false ;
                else{
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    frame2.push_back(temp2) ;
                    temp.F = true ;
                }

                for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                }

                temp.frameTemp = pageFrame ;
                MFUandFIFOTemp.push_back( temp ) ;
            }
            else {
                int numPlace ;
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame2.at(k).task == list.at(i) ) {
                        check = true;
                        numPlace = k ;
                    }

                }

                if ( !check ) {
                    pageReplace[3]++ ;
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    int eraserNum = frame2.at(0).weight;
                    int eraserPlace = 0 ;
                    for ( int q = 0 ;  q < frame2.size() ; q++ ) {
                        if ( frame2.at(q).weight > frame2.at(eraserPlace).weight) {
                            eraserPlace = q ;
                            eraserNum = frame2.at(q).weight ;
                        }

                    }
                    //cout <<eraserNum << endl ;
                    frame2.erase(frame2.begin() + eraserPlace) ;
                    frame2.push_back( temp2) ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = true ;
                    MFUandFIFOTemp.push_back( temp ) ;
                } // not have
                else {
                    frame2.at(numPlace).weight ++;
                    //cout << frame2.at(numPlace).task << "     " << frame2.at(numPlace).weight << endl ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = false ;
                    MFUandFIFOTemp.push_back( temp ) ;
                } // have num

            }
        } // 執行
    } // MFUandFIFO

    void MFUandLRU () {
        frame.clear();
        frame2.clear();
        pageReplace[4] = 0 ;
        Data temp ;
        weightData temp2 ;
        int checkPlace ;
        for ( int i = 0 ; i < list.size() ; i++ ) {
            bool check = false ;
            string pageFrame = "";
            if ( frame2.size() < numOfPageFrame) {
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    if ( frame2.at(k).task == list.at(i) ) {
                        check = true;
                        checkPlace = k ;
                    }

                } // 檢查是否已擁有
                if ( check)  {
                    temp.F = false ;
                    temp2.task = list.at(i) ;
                    temp2.weight = frame2.at(checkPlace).weight +1 ;
                    frame2.erase(frame2.begin() + checkPlace) ;
                    frame2.push_back( temp2) ;
                }
                else{
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    frame2.push_back(temp2) ;
                    temp.F = true ;
                }

                for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                }

                temp.frameTemp = pageFrame ;
                MFUandLRUTemp.push_back( temp ) ;
            }
            else {
                int numPlace ;
                for ( int k = 0 ; k < frame2.size() ; k++ ) {
                    //cout << frame.at(k) ;
                    if ( frame2.at(k).task == list.at(i) ) {
                        check = true;
                        numPlace = k ;
                    }

                }

                if ( !check ) {
                    pageReplace[4]++ ;
                    temp2.task = list.at(i) ;
                    temp2.weight = 0 ;
                    int eraserNum = frame2.at(0).weight;
                    int eraserPlace = 0 ;
                    for ( int q = 0 ;  q < frame2.size() ; q++ ) {
                        if ( frame2.at(q).weight > frame2.at(eraserPlace).weight) {
                            eraserNum =  frame2.at(q).weight ;
                            eraserPlace = q ;
                        }

                    }
                    frame2.erase(frame2.begin() + eraserPlace) ;
                    frame2.push_back( temp2) ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = true ;
                    MFUandLRUTemp.push_back( temp ) ;
                } // not have
                else {
                    temp2.task =frame2.at(numPlace).task ;
                    temp2.weight =frame2.at(numPlace).weight ;
                    temp2.weight ++ ;
                    frame2.erase(frame2.begin() + numPlace) ;
                    frame2.push_back( temp2) ;
                    for ( int j = (frame2.size() - 1) ; j >= 0 ; j-- ) {
                        pageFrame = pageFrame + frame2.at(j).task ;
                    }
                    temp.frameTemp = pageFrame ;
                    temp.F = false ;
                    MFUandLRUTemp.push_back( temp ) ;
                } // have num

            }
        } // 執行
    } // MFUandLRU

    void write () {
        fstream newFile;
        newFile.open("out_"+inputFileName+".txt", ios::out);
        int pageFault = 0 ;
        if ( method == 1  || method == 6) {
            newFile << "--------------FIFO-----------------------" << endl ;
            for ( int i = 0 ; i < list.size() ; i++ ) {
                newFile << list.at(i) << "\t" << FIFOTemp.at(i).frameTemp ;
                if ( FIFOTemp.at(i).F == true) {
                    newFile << "\tF" << endl ;
                    pageFault++ ;
                } // if
                else {
                    newFile << endl ;
                } // else
            }

            newFile << "Page Fault = " << pageFault << "  Page Replaces = " << pageReplace[0] << "  Page Frames = " << numOfPageFrame<< endl << endl;
        } // method 1
        if ( method == 2  || method == 6) {
            newFile << "--------------LRU-----------------------" << endl ;
            pageFault = 0 ;
            for ( int i = 0 ; i < list.size() ; i++ ) {
                newFile << list.at(i) << "\t" << LRUTemp.at(i).frameTemp ;
                if ( LRUTemp.at(i).F == true) {
                    newFile << "\tF" << endl ;
                    pageFault++ ;
                } // if
                else {
                    newFile << endl ;
                } // else
            }

            newFile << "Page Fault = " << pageFault << "  Page Replaces = " << pageReplace[1] << "  Page Frames = " << numOfPageFrame<< endl << endl;
        } // method 2
        if ( method == 3 || method == 6 ) {
            newFile << "--------------Least Frequently Used LRU Page Replacement-----------------------" << endl ;
            pageFault = 0 ;
            for ( int i = 0 ; i < list.size() ; i++ ) {
                newFile << list.at(i) << "\t" << LFUandLRUTemp.at(i).frameTemp ;
                if ( LFUandLRUTemp.at(i).F == true) {
                    newFile << "\tF" << endl ;
                    pageFault++ ;
                } // if
                else {
                    newFile << endl ;
                } // else
            }

            newFile << "Page Fault = " << pageFault << "  Page Replaces = " << pageReplace[2] << "  Page Frames = " << numOfPageFrame<< endl << endl;
        } // method 3

        if ( method == 4 || method == 6 ) {
            newFile << "--------------Most Frequently Used Page Replacement -----------------------" << endl ;
            pageFault = 0 ;
            for ( int i = 0 ; i < list.size() ; i++ ) {
                newFile << list.at(i) << "\t" << MFUandFIFOTemp.at(i).frameTemp ;
                if ( MFUandFIFOTemp.at(i).F == true) {
                    newFile << "\tF" << endl ;
                    pageFault++ ;
                } // if
                else {
                    newFile << endl ;
                } // else
            }

            newFile << "Page Fault = " << pageFault << "  Page Replaces = " << pageReplace[3] << "  Page Frames = " << numOfPageFrame<< endl << endl;
        } // method 4

        if ( method == 5 || method == 6) {
            newFile << "--------------Most Frequently Used LRU Page Replacement -----------------------" << endl ;
            pageFault = 0 ;
            for ( int i = 0 ; i < list.size() ; i++ ) {
                newFile << list.at(i) << "\t" << MFUandLRUTemp.at(i).frameTemp ;
                if ( MFUandLRUTemp.at(i).F == true) {
                    newFile << "\tF" << endl ;
                    pageFault++ ;
                } // if
                else {
                    newFile << endl ;
                } // else
            }

            newFile << "Page Fault = " << pageFault << "  Page Replaces = " << pageReplace[4] << "  Page Frames = " << numOfPageFrame<< endl ;
        } // method 5

        newFile.close();
    }

};
int main(void) {
    scheduling s;
    bool haveFile ;
	int command = -1;
	  do {
        cout << endl << "***     Page Replacement      ***" ;
        cout << endl << "* 0. Quit                       *" ;
        cout << endl << "* 1. Page Replacement           *" ;
        cout << endl << "*********************************" ;
        cout << endl << "Input a command( 0, 1 ) : " ;
        cin >> command ; // get the command

        switch(command){
            case 0 :
                break ;
            case 1 :
                s.reset() ;
                s.readFile() ;
                break ;
            default :
			cout << endl << "command does not exist !!" << endl ;
                break ;

	} // end switch

  } while ( command != 0 ) ;

}
