import java.net.*;
import java.io.*;

public class ClienteEspectador {

	private  static void executar()  throws Exception{
		Socket SOCKET = new Socket("localhost",1050);
		
		while(true){
			
			InputStreamReader IR = new InputStreamReader(SOCKET.getInputStream());
			BufferedReader BR = new BufferedReader(IR);
			
			String mensagemServidor = BR.readLine();
			
			int i = 0;
			
			while(i < 999){ 
				System.out.println(mensagemServidor);
				mensagemServidor = BR.readLine();
				i++;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		 executar();
	}
}
