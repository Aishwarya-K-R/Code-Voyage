package osproject;
import java.util.*;
class Process
{
	int no,at,bt,rt,ct,wt,tat,pri,temp,comp,pno;
	boolean finished=false;
}
public class PreemptivePriority
{
	static int min=-9999;
	static Scanner in=new Scanner(System.in);
	static Process read(int i)
	{
		Process p=new Process();
		System.out.println("Process No.: "+i);
		p.no=i;
		System.out.println("Enter Arrival Time :");
		p.at=in.nextInt();
		System.out.println("Enter Burst Time :");
		p.bt=in.nextInt();
		p.rt=p.bt;
		System.out.println("Enter Priority :");
		p.pri=in.nextInt();
		p.temp=p.pri;
		return p;
	}
	public static void main(String[]args)
	{
		int i,j,k=0,m,n,c,remaining,max_val,max_index;
		int comp[]=new int[100];
		int pno[]=new int[100];
		Process p[]=new Process[10];
		Process temp=new Process();
		float avgtat=0,avgwt=0;
		System.out.println("<----------Preemptive Priority Scheduling---------->");
		System.out.println("Enter the number of processes :");
		n=in.nextInt();
		for(i=0;i<n;i++)
		{
			p[i]=read(i+1);
		}
		remaining=n;
		for(i=0;i<n-1;i++)
		{
			for(j=0;j<n-i-1;j++)
			{
				if(p[j].at>p[j+1].at)
				{
					temp=p[j];
					p[j]=p[j+1];
					p[j+1]=temp;
				}
			}
		}
		max_val=p[0].temp;
		i=max_index=0;
		c=p[i].ct=p[i].at+1;
		p[i].rt--;
		for(m=0;m<n;m++)
		{
			if(c==p[m].at||p[i].rt==0)
			{
				pno[k]=i+1;
				comp[k]=c;
				k++;
				break;
			}
		}
		if(p[i].rt==0)
		{
			p[i].temp=min;
			remaining--;
		}
		while(remaining>0)
		{
			max_val=p[0].temp;
			max_index=0;
			for(j=0;j<n && p[j].at<=c;j++)
			{
				if(p[j].temp>max_val)
				{
					max_val=p[j].temp;
					max_index=j;
				}
			}
			i=max_index;
			p[i].ct=c=c+1;
			p[i].rt--;
			for(m=0;m<n;m++)
			{
				if(c==p[m].at||p[i].rt==0)
				{
					pno[k]=i+1;
					comp[k]=c;
					k++;
					break;
				}
			}
			if(p[i].rt==0)
			{
				p[i].temp=min;
				remaining--;
			}
		}
		System.out.println("Process No.\tAT\tBT\tPri\tCT\tTAT\tWT\n");
		for(i=0;i<n;i++)
		{
			p[i].tat=p[i].ct-p[i].at;
			avgtat+=p[i].tat;
			p[i].wt=p[i].tat-p[i].bt;
			avgwt+=p[i].wt;
			System.out.println("P"+p[i].no+"\t\t"+p[i].at+"\t"+p[i].bt+"\t"+p[i].pri+"\t"+p[i].ct+"\t"+p[i].tat+"\t"+p[i].wt);
		}
		avgtat/=n;
		avgwt/=n;
		System.out.println("\n<---------------Gantt Chart--------------->");
		System.out.print("| ");
		for(i=0;i<k;i++)
		{
			System.out.print("P"+pno[i]+" | ");
		}
		System.out.println();
		System.out.print("0 ");
		for(i=0;i<k;i++)
		{
			if(comp[i]>9)
			{
				System.out.print("  "+comp[i]+" ");
			}
			else
			{
				System.out.print("   "+comp[i]+" ");
			}
		}
		System.out.println();
		System.out.println("\nAverage Turn Around Time = "+avgtat);
		System.out.println("Average Waiting Time = "+avgwt);
	}
	}
	
