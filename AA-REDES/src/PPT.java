
public class PPT {

	public static String verificar(String player1, String player2){
		String vencedor = "";
		if(player1.equals("PEDRA")){
			if(player2.equals("PAPEL")){
				vencedor = "Jogador 2 ganhou! \n";
			}else if(player2.equals("TESOURA")){
				vencedor = "Jogador 1 ganhou! \n";
			}else if (player1.equals(player2)){
				vencedor = "Entradas iguais, empate! \n";
			}
		}else if(player1.equals("PAPEL")){
			if(player2.equals("PEDRA")){
				vencedor = "Jogador 1 ganhou! \n";
			}else if(player2.equals("TESOURA")){
				vencedor = "Jogador 2 ganhou! \n";
			}else if (player1.equals(player2)){
				vencedor = "Entradas iguais, empate! \n";
			}
		}else if(player1.equals("TESOURA")){
			if(player2.equals("PEDRA")){
				vencedor = "Jogador 2 ganhou! \n";
			}else if(player2.equals("PAPEL")){
				vencedor = "Jogador 1 ganhou! \n";
			}else if (player1.equals(player2)){
				vencedor = "Entradas iguais, empate! \n";
			}
		}else{
			vencedor = "Entrada foi inválida, repitam! \n";
		}
		return vencedor;
	}
	public static int ganhador(String ganhador){
		
		int vencedor = 0;
		
		if(ganhador.equals("Jogador 1 ganhou!")){
			vencedor++;
		}else{
			vencedor--;
		}
		
		
		return vencedor;
	}
}
