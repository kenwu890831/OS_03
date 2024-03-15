# OS_03

## 實作方法和流程 
➢ 程式開始執行時，依照使用者操作介面選取執行或是關
閉Page Replacement，可重複執行直到輸入0退出。 

➢ 根據使用者輸入的檔案名稱進行操作，使先檢查是否有
對應的檔案，有的話繼續執行程式，沒有的話輸出檔案
不存在的提示，並且重新輸入新的排程方式。 

➢ 確認正確讀檔之後，進行判別使用何種Page 
Replacement 方式，依照檔案指令執行。 

➢ 將執行完成後，將執行過程以及結果輸出至新的檔案，
依照範例格式寫入，寫入完成回到使用者介面。 

1. FIFO  
當Page Frame被放滿無法再放入其他Page時，就會將
在Memory 內最久的頁置換出去。 
2. LRU  
與FIFO頁置換法最大的不同在於，在 LRU頁置換法每
當此Page被參考到時，就會重新計算 Page的時間。 
3. LFU + LRU  
根據LRU每當有Page被參考到時，就會重新計算 Page
的時間，並且設立一個Counter，每當有Page被參考到
時Counter+1，。當遇到Page需要置換時，系統會選用
Counter 值最小的Page Frame做頁置換，如果Counter
相同則挑選較久的Page做頁置換。 
4. MFU + FIFO  
設立一個Counter，每當有Page被參考到時
Counter+1，。當遇到Page需要置換時，系統會選用
Counter 值最大的Page Frame做頁置換，如果Counter
相同則挑選較久的Page做頁置換。 
5. MFU + LRU  
根據LRU每當有Page被參考到時，就會重新計算 Page
的時間，並且設立一個Counter，每當有Page被參考到
時Counter+1，。當遇到Page需要置換時，系統會選用
Counter 值最大的Page Frame做頁置換，如果Counter
相同則挑選較久的Page做頁置換。 
## 不同排程法的比較 
(input1_methed6)( Page Fault/Page Replaces) 
* FIFO : 9/6 
* LRU : 10/7 
* LFU + LRU : 10/7 
* MFU + FIFO : 9/6 
* MFU + LRU : 9/6

(input2) ( Page Fault/Page Replaces) 
* FIFO : 15/12 
* LRU : 12/9 
* LFU + LRU : 11/8 
* MFU + FIFO : 15/12 
* MFU + LRU : 12/9

## 結果與討論 
我們從FIFO和LRU來比較，在input1_methed6時LRU發生
Page Fault 與 Page Replace 的次數皆比FIFO多，但在input2
中則相反LRU發生Page Fault與Page Replace的次數皆比
FIFO 少了3次，因此我認為在檔案多的時候FIFO的效率會比較
差，而LRU可以有效的減少Page Fault與Page Replace。 
而倆倆搭配的效果我認為會因為資料檔而會產生變化，並沒有
說哪個方法就比較優良。
