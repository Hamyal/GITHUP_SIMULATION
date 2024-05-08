
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class User {
private:
    string username;
    string password;
    int followers;

public:
    User();
    User(string uname, string pwd);
    string get_Username() const;
    string get_Password() const;
    int getFollowers() const;
    void Followers_add();
    void Followers_delete();
};

class File {
private:
    string name;

public:
    File(string n);
    string getName() const;
};

class commitment {
private:
    string message;

public:
    commitment(string msg);
    string getmessage_commit() const;
};

class Repository {
private:
    string name;
    bool pub;
    int commitCount;
    vector<File> files;
    vector<commitment> commits;
    vector<string> commitMessages;
   

public:
    Repository(string n, bool pub);
   
    bool Public_repository() const;
    void addFile(const File& file);
    void deleteFile(const string& fileName);
    const vector<File>& getFiles() const;
    void addCommit(const commitment& commit, const string& message);
    vector<string> Messages_commits() const;
    void set_Commit_Count(int count);
    const vector<commitment>& getCommits() const;
    string getName() const;
    void addCommit(const commitment& commit);
    int getFileCount() const;
    int Commit_Count() const;
};

class treeimplmentation {
private:

    Repository* repo;
    unordered_map<string, treeimplmentation*> children;

public:

    treeimplmentation(Repository* r);
    treeimplmentation* addChild(const string& name, Repository* repo);
    Repository* get_Repository() const;
    unordered_map<string, treeimplmentation*>& getChildren();
    ~treeimplmentation();
};

class githupsimulation {

private:

    unordered_map<string, User> users;
    unordered_map<string, treeimplmentation*> userRepositories;
    unordered_map<string, unordered_set<string>> followGraph;

public:

    githupsimulation();
    void login(string& loggedInUser);
    void logout(string& loggedInUser);
    void viewProfile(const string& usernameToView);
    void registerUser();
    void createRepository(const string& name, const string& repository_name, bool pub, int commitCount);
    void deleteRepository(const string& name, const string& repository_name);
    void addfile(const string& name, const string& repository_name, const string& fileName);
    void deletefile(const string& name, const string& repository_name, const string& fileName);
    void userdataread();
    void userwritedata();
    void readrepo();
    void writerepo();
    int countfork(const string& name, const string& repository_name);
    void Fork(const string& sourceUsername, const string& sourceRepoName, const string& find_username);
    void commitToRepository(const string& name, const string& repository_name, const string& message);
    void Statsrepository(const string& name, const string& repository_name);
    void Folllow(const string& follower, const string& following);
    void Unfolllow(const string& follower, const string& following);
};

