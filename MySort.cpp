#include <iostream>
#include <vector>
#include <algorithm>

/*
My understanding of Insertion Sort. 
IDEA: make use of the fact that elements from 0 to p -1 (passes) are already sorted.
We start checking from p = 1 to N-1 , comparing element at p with all before p.
*/

void mergeSort(std::vector<int>& data, std::vector<int>& copy, int left, int right);
void merge(std::vector<int>& data, std::vector<int>& copy, int left, int right, int rightEnd);
void quickSortImproved(std::vector<int>& data, int left, int right);

void insertionSort(std::vector<int>& data)
{
    for (size_t i = 1; i < data.size(); ++i) // all the passes
    {
        int comp = std::move(data[i]);

        size_t j;
        for (j=i;  j>0 && comp < data[j - 1] ; --j)
            data[j] = std::move(data[j-1]);

        data[j] = std::move(comp);

    }

    //method2
    /*
      for (size_t i = 1; i < data.size();++i)
    {
        for (size_t j = i; j > 0; --j)
            if (data[j] < data[j - 1])
                std::swap(data[j], data[j - 1]);
        
    }
    
    */
}

void selectionSort(std::vector<int>& data)
{

    for (size_t i = 0; i < data.size(); ++i)
    {
        
        size_t j;

        for (j = i+1; j < data.size(); ++j)
        {
            if (data[j] < data[i])
               std::swap(data[i],data[j]) ;

        }
        
    }
}

void shellSort(std::vector<int>& data)
{
    
    int gap = data.size() / 2;

    for (gap; gap > 0; gap /= 2)
    {
        int interval = gap;

        for (int i = 0; i + gap<data.size(); ++i)
        {
            
            if (data[i] > data[interval])            
                std::swap(data[i], data[interval]);              
                      
            
            if (i - gap > 0)          
            {                                               
                for (int j=i; j-gap >= 0; j -= gap)
                    if (data[j] < data[j - gap])                    
                        std::swap(data[j], data[j - gap]);                   
                                    
            }

            ++interval;
            
        }        
       
    }            
}


void mergeSortDriver(std::vector<int>& data, std::vector<int>& copy)
{
    
    mergeSort(data, copy, 0, data.size()-1); 
    
}

void mergeSort(std::vector<int>& data, std::vector<int>& copy, int left, int right)
{
    if (left<right)
    {

        int center = (right + left) / 2;
        
        mergeSort(data, copy, left, center); //go to left
        mergeSort(data, copy, center+1, right); //go to right
        merge(data,copy,left,center+1,right);        

        
    }
   
}

void merge(std::vector<int>& data, std::vector<int>& copy, int left, int right, int rightEnd)
{
    int leftEnd = right-1;    
    int tempPos = left;

    while (left <= leftEnd && right <= rightEnd)
    {
        if (data[left] > data[right])
            copy[tempPos++] = data[right++];
        else
            copy[tempPos++] = data[left++];
    }
    
    while (left <= leftEnd)
    {       
        copy[tempPos++]=data[left++];
    }

    while (right <= rightEnd)
    {
        copy[tempPos++] = data[right++];
    }

    for (int i = rightEnd; i >= 0; --i)
    {
        data[i] = copy[i];
    }
  
}

void quickSortBasic(std::vector<int>& data)
{
    if (data.size() > 1)
    {
        int pivot = data[data.size() / 2];

        std::vector<int> smaller;
        std::vector<int> same;
        std::vector<int> bigger;

        for (auto i : data)
        {
            if (i < pivot)
                smaller.push_back(i);
            else if (i == pivot)
                same.push_back(i);
            else if (i > pivot)
                bigger.push_back(i);
        }

        quickSortBasic(smaller);
        quickSortBasic(bigger);

        std::move(smaller.begin(), smaller.end(), data.begin());
        std::move(same.begin(), same.end(), data.begin()+smaller.size());
        std::move(bigger.begin(), bigger.end(), data.end() - bigger.size());



    }
}

void quickSortImprovedDriver(std::vector<int>& data)
{
    quickSortImproved(data, 0, data.size()- 1);
}

const int& getMedianofThree(std::vector<int>& data, int left, int right)
{
    int center = (left + right) / 2;
    if (data[center] < data[left])
        std::swap(data[left] , data[center]);
     if(data[right]<data[left])
        std::swap(data[left], data[right]);
     if(data[right]<data[center])
        std::swap(data[center], data[right]);

    std::swap(data[center], data[right]);

    return data[right];

}

void quickSortImproved(std::vector<int>& data, int left, int right)
{
    if (right-left>0)
    {
        const int& pivot = getMedianofThree(data, left, right);        
        int i = left-1;
        int j = right;
        std::cout << "pivot:" << pivot << " i and j:"<<i<<','<<j<<"\n";
        while (true)
        {
            
            while (data[++i] < pivot) {};
            while (data[--j] >pivot) {};

            if (i < j)
                std::swap(data[i], data[j]);
            else
                break;

        }
        
        std::swap(data[i], data[right]);

        quickSortImproved(data, left, i-1 );
        quickSortImproved(data, i+1, right);
    }
    

}

//Sorting strings if we know that they all got equal length
void radixLSDstringSort(std::vector<std::string>& data, int strlen)
{
    
    std::vector<std::vector<std::string>> buckets(ASCIINUM);

    for (int i = strlen-1; i >= 0; --i)
    {
        for (std::string &s : data)
        {
            buckets[s[i]].push_back(std::move(s));
        }

        int index{ 0 };

        for (auto &currentBucket : buckets)
        {
            for (std::string &s : currentBucket)
            {
                data[index++] = std::move(s);
                
            }
            currentBucket.clear();
        }
    }

}


int main()
{
    std::vector<int> data{ 3,5,1,2,8,58,120,56,37,98,456,85,6,8};
    shellSort(data); 
   

    std::vector<int> dataTwo{ 7,8,3,4,15,9,2,5,1,55,76,8,27,1,28,35,7,8 };    
    
    //mergeSortDriver(dataTwo,copy);
    //quickSort(dataTwo);

    quickSortImprovedDriver(dataTwo);
    for (auto i : dataTwo)
        std::cout << i << " ";    
   
    return 0;
    
}
