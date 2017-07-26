import javax.swing.*;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;


public class VendaTicketAluno {

	JFrame frame;
	public JRadioButton desjejum,alja;
	
	
	public VendaTicketAluno() {
		frame = new JFrame();
		frame.setBounds(550, 250, 300, 150);
		frame.setTitle("Vender Ticket");
		frame.setResizable(false);
		frame.getContentPane().setLayout(null);
		
		ButtonGroup preco = new ButtonGroup();
		
		desjejum = new JRadioButton("Pre\u00E7o Desjejum");
		desjejum.setBounds(6, 37, 163, 23);
		frame.getContentPane().add(desjejum);
		preco.add(desjejum);
		
		alja = new JRadioButton("Pre\u00E7o Almo\u00E7o/Jantar");
		alja.setBounds(6, 85, 163, 23);
		frame.getContentPane().add(alja);
		preco.add(alja);
		
		JButton btnVenderTicket = new JButton("Vender Ticket");
		btnVenderTicket.setBounds(175, 37, 109, 71);
		frame.getContentPane().add(btnVenderTicket);
		btnVenderTicket.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				venderClick();
			}
		});
		
	}
	private void venderClick(){
	float i;
	int j = TelaPrincipal.tabela.getSelectedRow();
	
		if(desjejum.isSelected()){			
		i = TelaPrincipal.db.getAlunos().get(j).getTicketsComprados() + (float) 0.5;	
		TelaPrincipal.db.getAlunos().get(j).setTicketsComprados(i);
		TelaPrincipal.tabela.preencheVazio();
		TelaPrincipal.tabela.preenche();		
		}
		else{		
		i = TelaPrincipal.db.getAlunos().get(j).getTicketsComprados() + (float) 1.0;
		TelaPrincipal.db.getAlunos().get(j).setTicketsComprados(i);
		TelaPrincipal.tabela.preencheVazio();
		TelaPrincipal.tabela.preenche();	
		}			
		
		frame.dispose();
	}
}
