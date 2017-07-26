import java.util.ArrayList;

import javax.swing.JTable;


public class TabelaFunc extends JTable{
	
	private ArrayList<Funcionario> rows;
	
	public void preenche(){
		for (int i = 0; i < rows.size(); i++) {
			this.setValueAt(rows.get(i).getNome(), i, 0);
			this.setValueAt(rows.get(i).getCPF(), i, 1);
			this.setValueAt(rows.get(i).getAnoIngresso(), i, 2);
			this.setValueAt(AdicionarFuncionario.comboBox.getSelectedItem(), i, 3);
			this.setValueAt(rows.get(i).getTicketsComprados(),i,4);
		}
	}
	
	public void preencheVazio(){
		for (int i = 0; i < rows.size()+1; i++) {
			this.setValueAt("", i, 0);
			this.setValueAt("", i, 1);
			this.setValueAt("", i, 2);
			this.setValueAt("",i,3);
			
		}
	}
	
	@Override
	public boolean isCellEditable(int row,int col){
		return false;
	}

	public TabelaFunc(ArrayList<Funcionario> rows, String[] columns){
		super(rows.size()+30,columns.length);
		this.rows = rows;
		
		for (int i = 0; i < columns.length; i++) {
			this.getColumnModel().getColumn(i).setHeaderValue(columns[i]);	
		}
		
		this.preenche();
	}
}