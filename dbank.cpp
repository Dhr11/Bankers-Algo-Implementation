#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<sstream>
#include<ctype.h>
#include<functional>
#include<map>

using namespace std;

struct process{
  int pid;
  int arrivaltime;
  vector<int> max;
  vector<int> allocated;
  vector<int> need;

  bool operator < (const process &b) const
  {
    if      (arrivaltime < b.arrivaltime)  return true;
    else   if ((arrivaltime == b.arrivaltime) && pid<b.pid)  return true;
    else return false;
  }
};

vector<int> tokenize(string inp)
{
  istringstream tmp(inp);
  std::vector<int> tokens;
  string token;
  for (std::string each; std::getline(tmp, each, ' '); tokens.push_back(atoi(each.c_str())));
  return tokens;
}


int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    cout<<"wrong no of parameters";
    exit(1);
  }
  string inFile       =argv[1];
  string outFile       =argv[2];
  istream *input = new ifstream(inFile, ios::in);
  ofstream output;
  output.open(outFile.c_str(), ios::out);
  if ( input->good() == false ) {
        cerr << "Error: The requested input file (" << inFile << ") could not be opened. Exiting!" << endl;
        exit (1);
    }

  string a;
  getline( *input, a, '\n' );
  vector<int> config=tokenize(a);
  if (config.size()!=3) {
        cerr << "Expected N R Q" << endl;
        exit (1);
    }

  vector<int> pid,artime;
  string b,c;
  getline( *input, b, '\n' );
  getline( *input, c, '\n' );
  pid=tokenize(b);


  artime=tokenize(c);
  vector<process> p;
  int maxwait(0);
  p.resize(*config.begin());
  for(std::vector<int>::size_type i=0;i<config[0];i++)
  {
    p[i].pid=pid[i];
    p[i].arrivaltime=artime[i];
    if(artime[i]>maxwait)
      maxwait=artime[i];
  }

  string d;
  getline( *input, d, '\n' );
  vector<int> available=tokenize(d);

  for(int i=0;i<config[0];i++)
  {
    string start;
    getline( *input, start, '\n' );
    p[i].max=tokenize(start);
  }
  for(int i=0;i<config[0];i++)
  {
    string start;
    getline( *input, start, '\n' );
    p[i].allocated=tokenize(start);
    std::transform(p[i].max.begin(),p[i].max.end(),p[i].allocated.begin(),std::back_inserter(p[i].need),std::minus<int>());
  }

  std::multimap<int,vector<int>> query;

  for(int i=0;i<config[2];i++)
  {
    string start;
    getline( *input, start, '\n' );
    vector<int> input;
    input=tokenize(start);
    int key=input[0];
    input.erase(input.begin());
    query.emplace(key,input);
  }


  sort(p.begin(),p.end());
vector<string> out;
vector<int> sequence;
vector<int> work=available;
std::pair<std::multimap<int, vector<int>>::iterator,
            std::multimap<int, vector<int>>::iterator> r;
vector<int> workartime=artime;
sort(workartime.begin(),workartime.end());


vector<int> zerovec;
for(int i=0;i<config[1];i++)
{
  zerovec.push_back(0);
}
int next;
int maxtimer=0;
int notsafe=0;
int totalprocess=p.size();
while(workartime.size()>0 && maxtimer<(maxwait*totalprocess))//maxwait>0)
{
  auto start=(p.begin());

  int countitem=std::count(workartime.begin(),workartime.end(),(*start).arrivaltime);  // no. of process at current time
  //cout<<"no of items in q:"<<countitem<<" with AT:"<<(*start).arrivaltime<<endl;
  // next arrival time note
  for(auto t=workartime.begin();t!=workartime.end();t++)
  {
    if(*t>(*start).arrivaltime)
      next=*t;
  }
  //cout<<"next:"<<next<<endl;
  auto end=(p.begin());
  for(;end!=p.end();end++)
  {
    if((*end).arrivaltime!=(*start).arrivaltime)
    {
      //end;
      break;
    }
  }
  //
  int grant=0;

  for(auto var=start;var!=end;var++)
  { //cout<<"process: "<<(*var).pid<<" AT:"<<(*var).arrivaltime<<endl;
    if(grant==1)              // if one prcoess in q is granted move others to +1 AT
    {
      auto tempit=std::find(workartime.begin(),workartime.end(),(*var).arrivaltime);
      (*tempit)+=1;
      (*var).arrivaltime+=1;
      //cout<<"updating time for process:"<<(*var).pid<<" at:"<<(*var).arrivaltime<<endl;
      continue;
    }
    r=query.equal_range((*var).pid);
    int cc=query.count((*var).pid);
    for(auto curquery=r.first;curquery!=r.second;curquery++)
    {
      vector<int> request=(*curquery).second;
      if(request>(*var).need)
        { output<<" request wrong";
          exit(1);
        }
      else
        { //(*var).need=(*var).need - request;
          if(request>work)
          {
            out.push_back("Deny");
            output<<"Deny"<<endl;
            continue;
          }
          else
          {
            vector<int> t1,t2,t3;
          std::transform(work.begin(),work.end(),request.begin(),std::back_inserter(t1),std::minus<int>());
          work=t1;
          std::transform((*var).allocated.begin(),(*var).allocated.end(),request.begin(),std::back_inserter(t2),std::plus<int>());
          (*var).allocated=t2;
          std::transform((*var).need.begin(),(*var).need.end(),request.begin(),std::back_inserter(t3),std::minus<int>());
          (*var).need=t3;
          out.push_back("Grant");
          output<<"Grant"<<endl;
          sequence.push_back((*var).pid);
          grant=1;

          if((*var).need==zerovec)
            {
              //cout<<"returning resources"<<endl;
              vector<int> t4;
              std::transform(work.begin(),work.end(),(*var).allocated.begin(),std::back_inserter(t4),std::plus<int>());
              work=t4;


              auto it=std::find(workartime.begin(),workartime.end(),(*var).arrivaltime);
              if(it!=workartime.end())
                workartime.erase(it);
              auto fordelete=var;
              var--;
              p.erase(fordelete);
              end--;
              //var=p.erase(var);
            }
            curquery=query.erase(curquery);
          if(cc!=1)//query.find((*var).pid)!=query.end())
          {
            auto tempit=std::find(workartime.begin(),workartime.end(),(*var).arrivaltime);
            (*tempit)+=1;
            (*var).arrivaltime+=1;
          }
          break;
          }

        }
      //after operating for current process in Q, either all query denied or one granted and break
    }
    if(grant==0) //all queries denied for a process then wait
    {
      auto tempit=std::find(workartime.begin(),workartime.end(),(*var).arrivaltime);
      (*tempit)+=1;
      //cout<<"updating time of process:"<<(*var).pid;
      (*var).arrivaltime+=1;
      //cout<<" AT now:"<<(*var).arrivaltime<<endl;
    }

  }   // queue at current time processed
  if(grant==0 && (*start).arrivaltime>maxwait)
  {
    notsafe=1;
    break;
  }
  sort(p.begin(),p.end());

  sort(workartime.begin(),workartime.end());
  maxtimer++;
  }
  if(notsafe==1)
  {
    output<<"Not Safe";
  }
  else
  for(auto it=sequence.begin();it!=sequence.end();it++)
  {
    output<<(*it)<<" ";
  }
  output.close();
  return 0;
}
