import { JSX, useState } from "react"
import { Typography, Modal, Input, Space, Button } from "antd"
import { FolderOpenOutlined, FolderAddOutlined, EditOutlined, FolderOutlined } from "@ant-design/icons"
import { useTranslation } from "react-i18next";

export default function ErrNoWorkspaceOpened():JSX.Element {
  const { t } = useTranslation();

  const [isWorkspaceCreationDialogOpened, setIsWorkspaceCreationDialogOpened] = useState(false)
  const [workspaceCreationDialogLoading, setWorkspaceCreationDialogLoading] = useState(false)

  const showWorkspaceCreationDialog = () => {
    setIsWorkspaceCreationDialogOpened(true)
  }

  const handleWorkspaceCreation = () => {
    setWorkspaceCreationDialogLoading(true)
    setTimeout(() => {
      setIsWorkspaceCreationDialogOpened(false);
      setWorkspaceCreationDialogLoading(false);
    }, 2000);
  }

  const handleWorkspaceCreationCancel = () => {
    setIsWorkspaceCreationDialogOpened(false)
  }

  return (
    <>
      <Modal
        title={t('create_workspace_title')}
        open={isWorkspaceCreationDialogOpened}
        confirmLoading={workspaceCreationDialogLoading}
        onOk={() => handleWorkspaceCreation()}
        onCancel={() => handleWorkspaceCreationCancel()}
        okText={t('ok_text')}
        cancelText={t('cancel_text')}>
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_name_label_desc')}
        </Typography.Text>
        <br className="no-select" draggable={false} />
        <Input className="no-select" prefix={<EditOutlined />} draggable={false} />

        <br className="no-select" draggable={false} />
        <br className="no-select" draggable={false} />
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_path_label_desc')}
        </Typography.Text>
        <br className="no-select" draggable={false} />
        <Space.Compact style={{ width: '100%' }}>
          <Input className="no-select" prefix={<FolderOutlined />} draggable={false} />
          <Button type="primary">{t('browse_action')}</Button>
        </Space.Compact>

        <br className="no-select" draggable={false} />
        <br className="no-select" draggable={false} />
        <Typography.Text className="app-text-smaller no-select" draggable={false}>
          {t('workspace_icon_settings_desc')}
        </Typography.Text>

        <br className="no-select" draggable={false} />
      </Modal>

      <div className="no-workspace-opened-container no-select">
        <Typography.Title level={2} className="no-select">
          {t('no_workspace_opened_title')}
        </Typography.Title>

        <Typography.Text className="app-text no-select">
          {t('open_workspace_desc')}
        </Typography.Text>

        <Typography>
          <ul>
            <li className="no-select">
              <Typography.Link className="app-text no-select">
                <FolderOpenOutlined />
                &nbsp;&nbsp;
                {t('open_workspace_action')}
              </Typography.Link>
            </li>

            <li className="no-select">
              <Typography.Link
                className="app-text no-select"
                onClick={() => showWorkspaceCreationDialog()}>
                <FolderAddOutlined />
                &nbsp;&nbsp;
                {t('create_workspace_action')}
              </Typography.Link>
            </li>
          </ul>
        </Typography>
      </div>
    </>
  )
}
