#include<iostream>
#define alphabets 26

using namespace std;
class TrieNode
{
public:
	string meaning;
	TrieNode* child[alphabets];
	int prefixCount;
	friend class Dictionary;


	TrieNode()
	{
		for (int i = 0; i < alphabets; i++)
			child[i] = NULL;
		meaning = "";
		prefixCount = 0;
	}
};

class Dictionary
{
	TrieNode* root;
	long long int totalWords;
public:
	Dictionary()
	{
		root = new TrieNode();
		totalWords=0;
	}

	~Dictionary()
	{
		clearDictionary(root);
	}
	void insert(string word, string word_meaning)
	{
		int index;
		totalWords++;
		TrieNode* temp =root;
		for (int i{};i<word.length();i++)
		{
			index = word[i] - 'a';
			if (temp->child[index] == NULL)
			{
				temp->child[index] = new TrieNode();
			}

			temp = temp->child[index];
			temp->prefixCount++;
		}

		temp->meaning = word_meaning;
	}

	bool isEmpty(TrieNode* temp)
	{
		for (int i{}; i < alphabets; i++)
			if (temp->child[i])
				return 0;

		return 1;
	}
	void autoComplete(TrieNode* root, string word, vector<string>& similarWords)
	{
		TrieNode* temp = root;
		
		if (root->meaning!="")
		{
			similarWords.push_back(word);
		}
		for (size_t i = 0; i < alphabets; i++)
		{
			if (temp->child[i])
				autoComplete(temp->child[i], word + (char)(i + 'a'),similarWords);
		}
	}
	 TrieNode* getRoot()
	{
		return root;
	}

	 void search(string word)
	 {
		 int index;
		 TrieNode* temp = root;
		 vector <string> similarWords;
		 for (size_t i = 0; i < word.length(); i++)
		 {
			 index = word[i] - 'a';
			 if (temp->child[index] == NULL)
			 {
				 autoComplete(temp, word.substr(0, i), similarWords);
				 break;
			 }
			 temp = temp->child[index];
		 }
		 if (temp->meaning == "")
			 autoComplete(temp, word, similarWords);

		 if (temp->meaning != "")
			 cout << "\n\tWord Found !! -  \"" << word << "\" -- meaning -->\"" << temp->meaning << "\n";
		 else
		 {
			 cout << "\n\tThe word \"" << word << "\" was not found "<<temp->prefixCount<<" matching words\n";
			 if (similarWords.size() == 0)
				 return;
			 cout << "\n\tDid you mean? ";
			 
			 for (size_t i = 0; i < similarWords.size() && i < 10; i++)
			 {
				 cout << similarWords[i];
				 (i == similarWords.size() - 1 || i == 9) ? cout<<"" : cout << " | ";
			 }
			 cout << "\n";
		 }

	 }
	 TrieNode* removeUtil(TrieNode* temp, string word, int depth = 0)
	 {
		 if (depth == word.size())
		 {
			 temp->meaning = "";
			 if (isEmpty(temp))
			 {
				 delete(temp);
				 temp = NULL;
			 }
			 return temp;

		 }
		 int index = word[depth] - 'a';
		 temp->child[index] = removeUtil(temp->child[index], word, depth + 1);
		 if (isEmpty(temp) && temp->meaning == "")
		 {
			 delete temp;
			 temp = NULL;
		 }
		 return temp;
	 }

	 void remove(string word)
	 {
		 removeUtil(root, word);
		 cout << "\n\t*****\"" << word << " removed Successfully ******\n. ";

	 }

	 TrieNode* clearDictionary(TrieNode* temp)
	 {
		 for (int i = 0; i < alphabets; i++)
		 {
			 if (temp->child[i])
				 temp->child[i] = clearDictionary(temp->child[i]);
		 }
		 delete temp;
		 temp = NULL;
		 return temp;
	 }
};