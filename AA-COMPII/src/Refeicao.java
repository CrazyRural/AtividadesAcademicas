import java.io.Serializable;


public class Refeicao implements Serializable {

	private Turno turno;
	private String Descricao;
	private String opcaoVegetariana;
	
	
	public String getOpcaoVegetariana() {
		return opcaoVegetariana;
	}
	public void setOpcaoVegetariana(String opcaoVegetariana) {
		this.opcaoVegetariana = opcaoVegetariana;
	}
	public String getDescricao() {
		return Descricao;
	}
	public void setDescricao(String descricao) {
		Descricao = descricao;
	}
	public Turno getTurno() {
		return turno;
	}
	public void setTurno(Turno turno) {
		this.turno = turno;
	}
	
	public Refeicao(String desc, String opVeg, Turno turno){
		this.setDescricao(desc);
		this.setTurno(turno);
		this.setOpcaoVegetariana(opVeg);
	}
}
