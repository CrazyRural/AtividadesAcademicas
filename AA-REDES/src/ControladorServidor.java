import java.net.*;
import java.io.*;

public abstract class ControladorServidor {
	
	public static void main(String[] args) throws Exception { 
		
		conectarClientes();		
	}
	
	 private static void conectarClientes() throws Exception{
		 
		ServerSocket SERVERSOCKET = new ServerSocket(1050);
		System.out.println("Servidor aguardando..."); 
		
		String mensagemEspectador = "";
		int ct = 0;
		
		Socket SOCKET = SERVERSOCKET.accept();
		Socket SOCKET1 = SERVERSOCKET.accept();
		Socket SOCKET2 = SERVERSOCKET.accept();
		
		if(ct == 0){
			mensagemEspectador = "Jogador 1 Conectado: "+SOCKET.getLocalAddress().getHostName() + "\n";			 
			System.out.println("1º Cliente Conectado");
			mensagemEspectador += "Jogador 2 Conectado: "+SOCKET1.getLocalAddress().getHostAddress()+"\n";
			System.out.println("2º Cliente Conectado");
			mensagemEspectador += "Jogador 2 Conectado: "+SOCKET2.getLocalAddress().getHostName()+"\n";
			System.out.println("3º Cliente Conectado");
		}
		while(true){
			
			InputStreamReader IR = new InputStreamReader(SOCKET.getInputStream());	
			BufferedReader BR = new BufferedReader(IR);		
			String mensagemCliente = BR.readLine();			
			
			if(mensagemCliente != null){			
				mensagemEspectador += "Jogador 1: "+mensagemCliente + "\n" ;
			}		
			
			InputStreamReader IR1 = new InputStreamReader(SOCKET1.getInputStream());
			BufferedReader BR1 = new BufferedReader(IR1);
			String mensagemCliente1 = BR1.readLine();
			
			if(mensagemCliente1 != null){
				mensagemEspectador += "Jogador 2: "+mensagemCliente1+"\n"; 
			}
			String vencedor = PPT.verificar(mensagemCliente, mensagemCliente1);
			
			mensagemEspectador += vencedor; 
			
			mensagemEspectador += "Fim da " + (ct + 1) +"º Rodada\n";
			
			PrintStream PS1 = new PrintStream(SOCKET.getOutputStream());
			PrintStream PS2 = new PrintStream(SOCKET1.getOutputStream());
			PrintStream PS3 = new PrintStream(SOCKET2.getOutputStream());
			
			PS1.println(vencedor);
			PS2.println(vencedor);
			PS3.print(mensagemEspectador);
			
			mensagemEspectador = "";
			
			ct++;
		}	
		
	}
}