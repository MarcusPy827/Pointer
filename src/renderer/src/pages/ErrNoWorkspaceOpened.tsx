import { JSX } from "react"
import { Typography } from "antd"
import { FolderOpenOutlined, FolderAddOutlined } from "@ant-design/icons"
import { useTranslation } from "react-i18next";

export default function ErrNoWorkspaceOpened():JSX.Element {
  const { t } = useTranslation();
  return (
    <>
      <div className="no-workspace-opened-container no-select">
        <Typography.Title level={2} className="no-select">{t('no_workspace_opened_title')}</Typography.Title>
        <Typography.Text className="app-text no-select">{t('open_workspace_desc')}</Typography.Text>
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
              <Typography.Link className="app-text no-select">
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
