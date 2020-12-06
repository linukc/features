## Basic commands
* <http://rightblog.ru/3274>
* <https://github.com/splincode/habrahabr-articles/tree/master/git>
* <http://johnatten.com/2012/09/08/basic-git-command-line-reference-for-windows-users/>
## Manual
* [from ya_luc](http://marklodato.github.io/visual-git-guide/index-ru.html)
* [extensive guide](https://git-scm.com/book/ru/v1/Îñíîâû-Git-Ñîçäàíèå-Git-ðåïîçèòîðèÿ)
* [basic instructions](https://proglib.io/p/git-for-half-an-hour/)
* [nicely done](https://www.atlassian.com/git/tutorials/learn-git-with-bitbucket-cloud)
* [great servies](https://githowto.com/ru/)
## Useful commands
### Preparation  
git config --global user.name "Your Name"  
git config --global user.email "your_email@whatever.com"  
### Creating a Project  
git init  
git add (git add .)    
git commit -m "Commit message"  
### Checking the status of the repository  
git status  
### History  
git log  
git history (git config --global alias.history "log --pretty=format:'%h %ad | %s%d [%an]' --graph --date=short")  
### Getting older versions  
git checkout \<hash\>  
git checkout master (return to latest version) 
### Print file
git cat \<file\>
### Tagging versions  
git tag    
git checkout \<tag\>^ (return to version before \<tag\>)    
git checkout \<tag\>  
git tag \<name\>  
git history master --all  
### Cancel local changes (before staging)  
Change file  
git checkout \<file\>  
### Cancel Staged changes (before committing)  
Change file  
git add \<file\>  
git reset HEAD \<file\> (The reset command resets the buffer to HEAD. This clears the buffer zone from the changes we just indexed. The reset command (the default) does not change the working directory. Therefore, the working directory still contains an unwanted   comment. We can use the checkout command to remove unwanted changes in the working directory.)  
git checkout \<file\>    
### Cancelling commits (it is also commit)    
Change file  
git add \<file\>  
git commit -m "Message commit"  
git revert HEAD (+ add commit message; if want leave editor press "esc" + input ":wq";--no-edit without editor) or  
git revert \<hash\>    
### Removing a commit from a branch  
git reset --hard \<tag\>  
git history --all   
(if we tag commit before delete we can whatever see the "delete" commit because he is still in repository with git history --all)  
### Delete tag  
git tag -d \<tag\>  
### Change last commit (don't create new commit)  
git add \<file\>  
git commit --amend -m "Add an author/email comment"  
### Move file  
git mv \<file\> \<dir\>  
### Сreate the branch  
git branch \<name\>  
git checkout \<name\> (switch to branch)  
### Branch merge (rebase!)    
git merge \<branch\>  (better for public using)  
### Rebase branch (merge!)  
git rebase \<branch\> (rewrite commit history)  
### Reset  
[with examples](https://git-scm.com/book/ru/v2/%D0%98%D0%BD%D1%81%D1%82%D1%80%D1%83%D0%BC%D0%B5%D0%BD%D1%82%D1%8B-Git-%D0%A0%D0%B0%D1%81%D0%BA%D1%80%D1%8B%D1%82%D0%B8%D0%B5-%D1%82%D0%B0%D0%B9%D0%BD-reset)

git reset --hard \<hash\>  
### Clone repo  
git clone \<repo_name_from\> \<new_repo_name\>  
git remote (list of remote repo)  
git remote show origin  
### Branch  
git branch (view local branch)  
git branch -a (view all branch)  
### Fetch commit to clone repo (1)
<img src="nWYnQ.png">

git fetch  
### Merge fetch commit (2)  
git merge origin/master  
(1) and (2) is equivalent to  
### git pull  
### Add local branch, which track origin branch  
git branch --track \<branch_name\> \<branch_name_from\>  
### Bare repo  

### Change push url  
git remote -v  
View existing remotes  
origin  https://github.com/user/repo.git (fetch)  
origin  https://github.com/user/repo.git (push)  

git remote set-url origin https://github.com/user/repo2.git  
Change the 'origin' remote URL    
git remote -v  
Verify new remote URL  
origin  https://github.com/user/repo2.git (fetch)  
origin  https://github.com/user/repo2.git (push) 

### GitHubFlow

https://guides.github.com/introduction/flow/

<img src="Screenshot from 2020-12-06 23-15-43.png">



