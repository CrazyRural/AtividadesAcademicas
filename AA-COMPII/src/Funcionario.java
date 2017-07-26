import java.io.Serializable;
import java.util.ArrayList;
import java.util.Arrays;

public class Funcionario extends Consumidor implements Serializable{

	private String departamento;
	
	public String getDepartamento() {
		return departamento;
	}

	public void setDepartamento(String object) {
		this.departamento = object;
	}
	
	
	static Object [][] array = { {"","","","",""} };

	ArrayList<Object> dadosFuncionarios = new ArrayList<Object>(Arrays.asList(array));
	
	public Funcionario(String nome, String anoIngresso,String cpf, String departamento){
		this.setNome(nome);
		this.setAnoIngresso(anoIngresso);
		this.setDepartamento(departamento);
		this.setCPF(cpf);
	}

	public Funcionario() {
		
	}	
}
