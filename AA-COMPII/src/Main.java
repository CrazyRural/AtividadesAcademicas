import java.io.Serializable;

import javax.swing.SwingUtilities;


public class Main implements Serializable {

	public static void main(String a[]){
		SwingUtilities.invokeLater(new Runnable(){
			@Override
			public void run(){
			 Login log = new Login();
			 log.frame.setVisible(true);
				
			}
		});
	}	
	
}
 

 